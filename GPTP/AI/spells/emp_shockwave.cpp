#include "spells.h"
#include <AI/ai_common.h>

// V241 for VS2008

namespace AI {

class EmpShockwaveTargetFinderShieldProc: public scbw::UnitFinderCallbackMatchInterface {

  private:
    CUnit* caster;

  public:
    EmpShockwaveTargetFinderShieldProc(CUnit* caster)
      : caster(caster) {}

    bool match(CUnit* target) {
		if (!isTargetWorthHitting(target, caster))
		  return false;

		if (!units_dat::ShieldsEnabled[target->id])
		  return false;

		if (!scbw::canWeaponTargetUnit(WeaponId::EMP_Shockwave, target, caster))
		  return false;

		const int totalEnemyShields = getTotalEnemyShieldsInArea(target->getX(), target->getY(), 160, caster);
		if (totalEnemyShields >= 200)
		  return true;

		return false;
    }
};

class EmpShockwaveTargetFinderEnergyProc: public scbw::UnitFinderCallbackMatchInterface {

  private:
    CUnit* caster;

  public:
    EmpShockwaveTargetFinderEnergyProc(CUnit* caster)
      : caster(caster) {}

    bool match(CUnit* target) {
		if (!isTargetWorthHitting(target, caster))
		  return false;

		if (!target->isValidCaster())
		  return false;

		if (!scbw::canWeaponTargetUnit(WeaponId::EMP_Shockwave, target, caster))
		  return false;

		const int totalEnemyEnergy = getTotalEnemyEnergyInArea(target->getX(), target->getY(), 160, caster);
		if (totalEnemyEnergy >= 200)
		  return true;

		return false;
    }
};

CUnit* findBestEmpShockwaveTarget(CUnit* caster, bool isUnderAttack) {

  int bounds;

  if (isUnderAttack)
    bounds = 32 * 9;
  else
    bounds = 32 * 64;

  CUnit* result = scbw::UnitFinder::getNearestTarget(
    caster->getX() - bounds, caster->getY() - bounds,
    caster->getX() + bounds, caster->getY() + bounds,
    caster, EmpShockwaveTargetFinderShieldProc(caster));

  if (result || isUnderAttack)
    return result;

  return scbw::UnitFinder::getNearestTarget(
    caster->getX() - bounds, caster->getY() - bounds,
    caster->getX() + bounds, caster->getY() + bounds,
    caster, EmpShockwaveTargetFinderEnergyProc(caster));
}

} //AI