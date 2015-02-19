#include "update_status_effects.h"
#include <SCBW/api.h>
#include <SCBW/enumerations.h>
#include <SCBW/scbwdata.h>
#include <SCBW/UnitFinder.h>
#include <algorithm>

//V241 for VS2008

class irradiateProc : public scbw::UnitFinderCallbackProcInterface {

  private:
    CUnit *irradiatedUnit;

  public:
    irradiateProc(CUnit *irradiatedUnit)
      : irradiatedUnit(irradiatedUnit) {}

	void proc(CUnit *unit) {
		//Damage organic units only
		if (!(units_dat::BaseProperty[unit->id] & UnitProperty::Organic))
		  return;

		//Don't damage buildings
		if (units_dat::BaseProperty[unit->id] & UnitProperty::Building)
		  return;

		//Don't damage larvae, eggs, and lurker eggs
		if (unit->id == UnitId::larva || unit->id == UnitId::egg || unit->id == UnitId::lurker_egg)
		  return;

		//Irradiate splash damage does not affect burrowed units
		if (unit != irradiatedUnit && unit->status & UnitStatus::Burrowed)
		  return;

		//Check if the unit is within distance, or is inside the same transport
		if (irradiatedUnit->status & UnitStatus::InTransport
			|| irradiatedUnit->getDistanceToTarget(unit) <= 32)
		{
		  const s32 damage = weapons_dat::DamageAmount[WeaponId::Irradiate] * 256 / weapons_dat::Cooldown[WeaponId::Irradiate];
		  unit->damageWith(damage, WeaponId::Irradiate, irradiatedUnit->irradiatedBy, irradiatedUnit->irradiatePlayerId);
		}
    }
};

namespace hooks {

//Applies Irradiate effects for @p unit (which is Irradiated)
void doIrradiateDamage(CUnit *irradiatedUnit) {
  //Default StarCraft behavior

  irradiateProc irradiation=irradiateProc(irradiatedUnit);

  //No splash if burrowed
  if (irradiatedUnit->status & UnitStatus::Burrowed) {
	  irradiation.proc(irradiatedUnit);
  }
  //If inside a transport, damage all units loaded within
  else if (irradiatedUnit->status & UnitStatus::InTransport) {

    const CUnit *transport = irradiatedUnit->connectedUnit;

    if (transport != NULL) {
      for (int i = 0; i < units_dat::SpaceProvided[transport->id]; ++i) {
        CUnit *loadedUnit = transport->getLoadedUnit(i);
        if (loadedUnit)
			irradiation.proc(loadedUnit);
      }
    }

  }
  //Find and iterate nearby units
  else {
    scbw::UnitFinder unitFinder(irradiatedUnit->getX() - 160,
                                irradiatedUnit->getY() - 160,
                                irradiatedUnit->getX() + 160,
                                irradiatedUnit->getY() + 160);
    unitFinder.forEach(irradiation);
  }
}

//Hook function for UpdateStatusEffects() (AKA RestoreAllUnitStats())
//Note: This function is called every 8 ticks (when unit->cycleCounter reaches 8 == 0)
void updateStatusEffectsHook(CUnit *unit) {
  //Default StarCraft logic

  if (unit->stasisTimer) {
    unit->stasisTimer--;
    if (unit->stasisTimer == 0)
      unit->removeStasisField();
  }

  if (unit->stimTimer) {
    unit->stimTimer--;
    if (unit->stimTimer == 0)
      unit->updateSpeed();
  }

  if (unit->ensnareTimer) {
    unit->ensnareTimer--;
    if (unit->ensnareTimer == 0) {
      unit->removeOverlay(ImageId::EnsnareOverlay_Small, ImageId::EnsnareOverlay_Large);
      unit->updateSpeed();
    }
  }

  if (unit->defensiveMatrixTimer) {
    unit->defensiveMatrixTimer--;
    if (unit->defensiveMatrixTimer == 0) {
      unit->reduceDefensiveMatrixHp(unit->defensiveMatrixHp);
    }
  }

  if (unit->irradiateTimer) {
    unit->irradiateTimer--;
    doIrradiateDamage(unit);
    if (unit->irradiateTimer == 0) {
      unit->removeOverlay(ImageId::Irradiate_Small, ImageId::Irradiate_Large);
      unit->irradiatedBy = NULL;
      unit->irradiatePlayerId = 8;
    }
  }

  if (unit->lockdownTimer) {
    unit->lockdownTimer--;
    if (unit->lockdownTimer == 0)
      unit->removeLockdown();
  }

  if (unit->maelstromTimer) {
    unit->maelstromTimer--;
    if (unit->maelstromTimer == 0)
      unit->removeMaelstrom();
  }

  if (unit->plagueTimer) {
    unit->plagueTimer--;
    if (!(unit->status & UnitStatus::Invincible)) {
      s32 damage = (weapons_dat::DamageAmount[WeaponId::Plague] << 8) / 76;
      if (unit->hitPoints > damage)
        unit->damageHp(damage);
    }
    if (unit->plagueTimer == 0)
      unit->removeOverlay(ImageId::PlagueOverlay_Small, ImageId::PlagueOverlay_Large);
  }

  if (unit->isUnderStorm)
    unit->isUnderStorm--;

  u8 previousAcidSporeCount = unit->acidSporeCount;
  for (int i = 0; i <= 8; ++i) {
    if (unit->acidSporeTime[i]) {
      unit->acidSporeTime[i]--;
      if (unit->acidSporeTime[i] == 0)
        unit->acidSporeCount--;
    }
  }
  if (unit->acidSporeCount) {
    //Calculate the appropriate overlay ID
    //TODO: Move this into a separate hook module (see GetAcidSporeImage())
    u32 acidOverlayId = std::min(3, unit->acidSporeCount / 2)
                      + 4 * scbw::getUnitOverlayAdjustment(unit)
                      + ImageId::AcidSpores_1_Overlay_Small;

    if (!unit->getOverlay(acidOverlayId)) {
      unit->removeOverlay(ImageId::AcidSpores_1_Overlay_Small, ImageId::AcidSpores_6_9_Overlay_Large);
      if (unit->subunit)
        unit = unit->subunit;
      unit->sprite->createTopOverlay(acidOverlayId);
    }
  }
  else if (previousAcidSporeCount) {
    unit->removeOverlay(ImageId::AcidSpores_1_Overlay_Small, ImageId::AcidSpores_6_9_Overlay_Large);
  }
}

} //hooks