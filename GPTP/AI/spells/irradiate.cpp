#include "spells.h"
#include <AI/ai_common.h>

//V241 for VS2008

namespace AI {

class IrradiateTargetFinderProc: public scbw::UnitFinderCallbackMatchInterface {

  private:
    CUnit* caster;
    bool isUnderAttack;

  public:
    IrradiateTargetFinderProc(CUnit* caster, bool isUnderAttack)
      : caster(caster), isUnderAttack(isUnderAttack) {}

    bool match(CUnit* target) {

		if (!isTargetWorthHitting(target, caster))
		  return false;

		if (target->irradiateTimer)
		  return false;

		if (!scbw::canWeaponTargetUnit(WeaponId::Irradiate, target, caster))
		  return false;

		if (!(units_dat::BaseProperty[target->id] & UnitProperty::Organic))
		  return false;

		if (units_dat::BaseProperty[target->id] & UnitProperty::Building)
		  return false;

		if (target->id == UnitId::larva
			|| target->id == UnitId::egg
			|| target->id == UnitId::lurker_egg)
		  return false;

		if (isUnderAttack || !isUmsMode(caster->playerId))
		  return true;

		if (units_dat::BaseProperty[target->id] & UnitProperty::Worker)
		  return true;

		if (target->id == UnitId::overlord || target->id == UnitId::medic)
		  return true;

		return false;

    }
};

CUnit* findBestIrradiateTarget(CUnit* caster, bool isUnderAttack) {

  int bounds;

  if (isUnderAttack)
    bounds = 32 * 9;
  else
    bounds = 32 * 64;

  return scbw::UnitFinder::getNearestTarget(
    caster->getX() - bounds, caster->getY() - bounds,
    caster->getX() + bounds, caster->getY() + bounds,
    caster, IrradiateTargetFinderProc(caster,isUnderAttack));
}

} //AI
