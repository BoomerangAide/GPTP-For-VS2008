#include "ai_common.h"
#include <SCBW/enumerations.h>
#include <SCBW/api.h>
#include <SCBW/UnitFinder.h>
#include <cassert>

namespace AI {

//Equivalent to 00440E30 AI_TargetUnitIsWorthHitting
bool isTargetWorthHitting(CUnit* target, CUnit* attacker) {

  //If the target is hidden by the fog-of-war
  if (!target->sprite->isVisibleTo(attacker->playerId))
    return false;

  //If the target is not detectable
  if (target->status & (UnitStatus::Cloaked + UnitStatus::RequiresDetection)
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

bool isTargetAttackingAlly(CUnit* target, CUnit* unit) {
  if (CUnit* targetOfTarget = target->orderTarget.unit) {
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

//Based on code @ 0x00440BB0 (not a real independant function)
bool isUnitInUnsafeRegion(CUnit* unit) {
  u16 currentRegion = getRegionIdAtPosEx(unit->getX(), unit->getY());
  AiCaptain *currentAiCaptain = &AiRegionCaptains[unit->playerId][currentRegion];
  return currentAiCaptain->captainType == 3
    || currentAiCaptain->unknown_0x1C
    || currentAiCaptain->unknown_0x20
    || currentAiCaptain->captainFlags & 0x20;
}


//-------- Get total unit stats in area --------//

//00440A60  unitShieldsClumpInAreaAccumulatorProc
//00440AC0  unitEnergyClumpInAreaAccumulatorProc
//00440B20  getEnemyClumpValueProc
//00440CF0  AIEnemyOrganicUnitHPAccumulatorProc
//00440D60  AIAllyUnitHPAccumulatorProc
//00440DC0  AIEnemyUnitHPAccumulatorProc
//00440FF0  FindNearestEnemyAndClumpProc


scbw::UnitFinder unitStatTotalFinder;

//In original functions:
//0x00695604 would contains weaponId
//0x00695798 would contains totalEnemyLife
int getTotalEnemyLifeInArea(int x, int y, int searchBounds, CUnit* caster, u8 weaponId) {

	unitStatTotalFinder.search(x - searchBounds, y - searchBounds,
                             x + searchBounds, y + searchBounds);

	int totalEnemyLife = 0;

	for (int i = 0; i < unitStatTotalFinder.getUnitCount(); ++i) {

		CUnit* target = unitStatTotalFinder.getUnit(i);

		if(
			(target != caster) &&
			!(target->status & UnitStatus::Invincible) &&
			scbw::canWeaponTargetUnit(weaponId, target, caster) &&
			caster->isTargetEnemy(target)
			)
		{

			//specific to AIEnemyUnitHPAccumulatorProc @ 0x00440DC0
			if (weaponId == WeaponId::Plague)
				totalEnemyLife += target->getCurrentHpInGame();
			else 
			//specific to AIEnemyOrganicUnitHPAccumulatorProc @ 0x00440CF0
			//used only by Maelstrom
			if (weaponId == WeaponId::Maelstrom) {

				if (
					units_dat::BaseProperty[target->id] & UnitProperty::Organic &&
					target->maelstromTimer == 0
				  ) 
					totalEnemyLife += target->getCurrentLifeInGame();

			}
			else
			  totalEnemyLife += target->getCurrentLifeInGame();

		}

		//bool bStopChecking = false;

		//if (target == caster)
		//  bStopChecking = true;

		//if (!bStopChecking && (target->status & UnitStatus::Invincible))
		//  bStopChecking = true;

		//if (!bStopChecking && !scbw::canWeaponTargetUnit(weaponId, target, caster))
		//  bStopChecking = true;

		//if (!bStopChecking && !caster->isTargetEnemy(target))
		//  bStopChecking = true;

		//if(!bStopChecking) {
		//	if (weaponId == WeaponId::Plague)
		//	  totalEnemyLife += target->getCurrentHpInGame();
		//	else if (weaponId == WeaponId::Maelstrom) {
		//	  if (units_dat::BaseProperty[target->id] & UnitProperty::Organic
		//		  && target->maelstromTimer == 0) {
		//		totalEnemyLife += target->getCurrentLifeInGame();
		//	  }
		//	}
		//	else
		//	  totalEnemyLife += target->getCurrentLifeInGame();
		//}

  }

  return totalEnemyLife;
}

//Loop content based on AIAllyUnitHPAccumulatorProc @ 0x00440D60
//0x00695798 would contains totalAllyLife
int getTotalAllyLifeInArea(int x, int y, int searchBounds, CUnit* caster, u8 weaponId) {

	unitStatTotalFinder.search(x - searchBounds, y - searchBounds,
							 x + searchBounds, y + searchBounds);

	int totalAllyLife = 0;

	for (int i = 0; i < unitStatTotalFinder.getUnitCount(); ++i) {

		CUnit* target = unitStatTotalFinder.getUnit(i);

		if(
			!(target->status & UnitStatus::Invincible) &&
			scbw::canWeaponTargetUnit(weaponId, target, caster) &&
			!caster->isTargetEnemy(target)
		)
			totalAllyLife += target->getCurrentLifeInGame();

  }

  return totalAllyLife;

}

//Loop content based on unitShieldsClumpInAreaAccumulatorProc @ 0x00440A60
//0x00695798 would contains totalEnemyShields
int getTotalEnemyShieldsInArea(int x, int y, int searchBounds, CUnit* caster) {

	unitStatTotalFinder.search(x - searchBounds, y - searchBounds,
                             x + searchBounds, y + searchBounds);
  
	int totalEnemyShields = 0;

	for (int i = 0; i < unitStatTotalFinder.getUnitCount(); ++i) {

		CUnit* target = unitStatTotalFinder.getUnit(i);

		if(
			!(target->status & UnitStatus::Invincible) &&
			caster->isTargetEnemy(target) &&
			units_dat::ShieldsEnabled[target->id]
		)
			totalEnemyShields += target->getCurrentShieldsInGame();

	}

	return totalEnemyShields;

}

//Loop content based on unitEnergyClumpInAreaAccumulatorProc @ 0x00440AC0
//0x00695798 would contains totalEnemyEnergy
int getTotalEnemyEnergyInArea(int x, int y, int searchBounds, CUnit* caster) {

	unitStatTotalFinder.search(x - searchBounds, y - searchBounds,
                             x + searchBounds, y + searchBounds);

	int totalEnemyEnergy = 0;

	for (int i = 0; i < unitStatTotalFinder.getUnitCount(); ++i) {

		CUnit* target = unitStatTotalFinder.getUnit(i);

		if(
			!(target->status & UnitStatus::Invincible) &&
			caster->isTargetEnemy(target) &&
			target->isValidCaster()
		)
			totalEnemyEnergy += (&target->energy)[1];	//unitPointer+0xA3 in original code

  }

  return totalEnemyEnergy;

}

//Content based on	AI_NukeRequirementsProc @ 0x00441600 and
//					getEnemyClumpValueProc	@ 0x00440B20
//0x00695798 would contains totalNukeTargetValue
//Optimized to stop when reaching totalNukeTargetValue == 800 since that's what matter
int getTotalEnemyNukeValueInArea(int x, int y, int searchBounds, CUnit* caster) {

	unitStatTotalFinder.search(x - searchBounds, y - searchBounds,
                             x + searchBounds, y + searchBounds);
  
	int totalNukeTargetValue = 0;

	for (int i = 0; i < unitStatTotalFinder.getUnitCount() && totalNukeTargetValue < 800; ++i) {

		CUnit* target = unitStatTotalFinder.getUnit(i);

		if(
			!(target->status & UnitStatus::Invincible) &&
			caster->isTargetEnemy(target)
			)
		{

			if( (units_dat::BaseProperty[target->id] & UnitProperty::Worker) ||
				( !(target->status & UnitStatus::IsBuilding) )
				)
				totalNukeTargetValue += target->getCurrentLifeInGame();

			if(units_dat::BaseProperty[target->id] & UnitProperty::Building) {

				if(	target->canDetect() ||
					target->id == UnitId::ZergSunkenColony ||
					target->id == UnitId::ZergLurker
				)
					totalNukeTargetValue = 800; //0x0320

			}

		}

  }

  return totalNukeTargetValue;
}

} //AI
