#include "spells.h"
#include <AI/ai_common.h>

//V241 for VS2008

namespace AI {

	class PlagueTargetFinderProc: public scbw::UnitFinderCallbackMatchInterface {

	  private:
		CUnit* caster;
		bool isUnderAttack;

	  public:
		PlagueTargetFinderProc(CUnit* caster, bool isUnderAttack)
		  : caster(caster), isUnderAttack(isUnderAttack) {}

		bool match(CUnit* target) {
			if (!isTargetWorthHitting(target, caster))
			  return false;

			if (!scbw::canWeaponTargetUnit(WeaponId::Plague, target, caster))
			  return false;

			if (target->plagueTimer)
			  return false;

			if (units_dat::BaseProperty[target->id] & UnitProperty::Hero)
			  return false;

			const int totalEnemyLife = getTotalEnemyLifeInArea(target->getX(), target->getY(), 96, caster, WeaponId::Plague);
			if (!isUnderAttack && totalEnemyLife < 250)
			  return false;

			const int totalAllyLife = getTotalAllyLifeInArea(target->getX(), target->getY(), 96, caster, WeaponId::Plague);
			if (totalAllyLife * 2 >= totalEnemyLife)
			  return false;

			return true;
		}
	};

	CUnit* findBestPlagueTarget(CUnit* caster, bool isUnderAttack) {

	  int bounds;

	  if (isUnderAttack)
		bounds = 32 * 9;
	  else
		bounds = 32 * 128;

	  return scbw::UnitFinder::getNearestTarget(
		caster->getX() - bounds, caster->getY() - bounds,
		caster->getX() + bounds, caster->getY() + bounds,
		caster, PlagueTargetFinderProc(caster,isUnderAttack));
	}

} //AI
