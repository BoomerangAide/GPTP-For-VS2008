#include "ai_common.h"
#include <SCBW/enumerations.h>
#include <SCBW/api.h>
#include <SCBW/UnitFinder.h>
#include <cassert>

//V241 for VS2008

namespace AI {

bool isTargetWorthHitting(const CUnit *target, const CUnit *attacker) {
  //If the target is hidden by the fog-of-war
  if (!target->sprite->isVisibleTo(attacker->playerId))
    return false;

  //If the target is not detectable
  if (target->status & (UnitStatus::Cloaked | UnitStatus::RequiresDetection)
      && !target->isVisibleTo(attacker->playerId))
    return false;

  if (!attacker->isTargetEnemy(target))
    return false;

  if (target->id == UnitId::scarab
      || target->id == UnitId::spider_mine
      || target->id == UnitId::interceptor)
    return false;

  //Target is a worker inside a gas building
  if (target->mainOrderId == OrderId::HarvestGas1
      || target->mainOrderId == OrderId::HarvestGas2
      || target->mainOrderId == OrderId::HarvestGas3)
    return false;

  return true;
}

bool isTargetAttackingAlly(const CUnit *target, const CUnit *unit) {
  if (CUnit *targetOfTarget = target->orderTarget.unit) {
    if (targetOfTarget->playerId < 8 && !unit->isTargetEnemy(targetOfTarget))
      return true;
  }

  return false;
}

bool isUmsMode(u8 playerId) {
  assert(playerId < 8);
  return AIScriptController[playerId].AI_Flags.isUseMapSettings;
}

//-------- isUnitInUnsafeRegion() --------//

//Internal use only
const u32 Func_GetRegionIdAtPosEx = 0x0049C9F0;
u16 getRegionIdAtPosEx(s32 x, s32 y) {
  static u16 result;

  __asm {
    PUSHAD
    MOV EDI, x
    MOV ECX, y
    CALL Func_GetRegionIdAtPosEx
    MOV result, AX
    POPAD
  }

  return result;
}

//Based on code @ 0x00440BB0
bool isUnitInUnsafeRegion(const CUnit *unit) {
  u16 currentRegion = getRegionIdAtPosEx(unit->getX(), unit->getY());
  AiCaptain *currentAiCaptain = &AiRegionCaptains[unit->playerId][currentRegion];
  return currentAiCaptain->captainType == 3
    || currentAiCaptain->unknown_0x1C
    || currentAiCaptain->unknown_0x20
    || currentAiCaptain->captainFlags & 0x20;
}


//-------- Get total unit stats in area --------//

scbw::UnitFinder unitStatTotalFinder;

int getTotalEnemyLifeInArea(int x, int y, int searchBounds, const CUnit *caster, u8 weaponId) {

  unitStatTotalFinder.search(x - searchBounds, y - searchBounds,
                             x + searchBounds, y + searchBounds);

  int totalEnemyLife = 0;

  for (int i = 0; i < unitStatTotalFinder.getUnitCount(); ++i) {

	  CUnit* target = unitStatTotalFinder.getUnit(i);
	  bool bStopChecking = false;

		if (target == caster)
		  bStopChecking = true;

		if (!bStopChecking && (target->status & UnitStatus::Invincible))
		  bStopChecking = true;

		if (!bStopChecking && !scbw::canWeaponTargetUnit(weaponId, target, caster))
		  bStopChecking = true;

		if (!bStopChecking && !caster->isTargetEnemy(target))
		  bStopChecking = true;

		if(!bStopChecking) {
			if (weaponId == WeaponId::Plague)
			  totalEnemyLife += target->getCurrentHpInGame();
			else if (weaponId == WeaponId::Maelstrom) {
			  if (units_dat::BaseProperty[target->id] & UnitProperty::Organic
				  && target->maelstromTimer == 0) {
				totalEnemyLife += target->getCurrentLifeInGame();
			  }
			}
			else
			  totalEnemyLife += target->getCurrentLifeInGame();
		}

  }

  return totalEnemyLife;
}

int getTotalAllyLifeInArea(int x, int y, int searchBounds, const CUnit *caster, u8 weaponId) {

  unitStatTotalFinder.search(x - searchBounds, y - searchBounds,
                             x + searchBounds, y + searchBounds);

  int totalAllyLife = 0;

  for (int i = 0; i < unitStatTotalFinder.getUnitCount(); ++i) {

	  CUnit* target = unitStatTotalFinder.getUnit(i);
	  bool bStopChecking = false;

		if (target == caster)
		  bStopChecking = true;

		if (!bStopChecking && (target->status & UnitStatus::Invincible))
		  bStopChecking = true;

		if (!bStopChecking && !scbw::canWeaponTargetUnit(weaponId, target, caster))
		  bStopChecking = true;

		if (!bStopChecking && caster->isTargetEnemy(target))
		  bStopChecking = true;

		if(!bStopChecking)
			totalAllyLife += target->getCurrentLifeInGame();

  }

  return totalAllyLife;
}

int getTotalEnemyShieldsInArea(int x, int y, int searchBounds, const CUnit *caster) {

	unitStatTotalFinder.search(x - searchBounds, y - searchBounds,
                             x + searchBounds, y + searchBounds);
  
	int totalEnemyShields = 0;

	for (int i = 0; i < unitStatTotalFinder.getUnitCount(); ++i) {

		CUnit* target = unitStatTotalFinder.getUnit(i);
		bool bStopChecking = false;

		if (target->status & UnitStatus::Invincible)
		  bStopChecking = true;

		if (!bStopChecking && !caster->isTargetEnemy(target))
		  bStopChecking = true;

		if(!bStopChecking && units_dat::ShieldsEnabled[target->id])
			totalEnemyShields += target->getCurrentShieldsInGame();

	}

	return totalEnemyShields;

}

int getTotalEnemyEnergyInArea(int x, int y, int searchBounds, const CUnit *caster) {

  unitStatTotalFinder.search(x - searchBounds, y - searchBounds,
                             x + searchBounds, y + searchBounds);

  int totalEnemyEnergy = 0;

  for (int i = 0; i < unitStatTotalFinder.getUnitCount(); ++i) {

		CUnit* target = unitStatTotalFinder.getUnit(i);
		bool bStopChecking = false;

		if (target->status & UnitStatus::Invincible)
		  bStopChecking = true;

		if (!bStopChecking && !caster->isTargetEnemy(target))
		  bStopChecking = true;

		if (!bStopChecking && !target->isValidCaster())
		  bStopChecking = true;

		if(!bStopChecking)
			totalEnemyEnergy += target->energy / 256;

  }

  return totalEnemyEnergy;
}

int getTotalEnemyNukeValueInArea(int x, int y, int searchBounds, const CUnit *caster) {

  unitStatTotalFinder.search(x - searchBounds, y - searchBounds,
                             x + searchBounds, y + searchBounds);
  
  int totalNukeTargetValue = 0;

  for (int i = 0; i < unitStatTotalFinder.getUnitCount(); ++i) {

		CUnit* target = unitStatTotalFinder.getUnit(i);
		bool bStopChecking = false;

		if (target->status & UnitStatus::Invincible)
		  bStopChecking = true;

		if (!bStopChecking && 
			(units_dat::BaseProperty[target->id] & UnitProperty::Worker)
			|| !(target->status & UnitStatus::IsBuilding))
		  totalNukeTargetValue += target->getCurrentLifeInGame();

		if (!bStopChecking && (
			units_dat::BaseProperty[target->id] & UnitProperty::Building)) {

			  if (target->canDetect()
				  || target->id == UnitId::sunken_colony
				  || target->id == UnitId::lurker)
				totalNukeTargetValue = 800;  //Any static defense is at least 800 value

		}

  }

  return totalNukeTargetValue;
}

} //AI