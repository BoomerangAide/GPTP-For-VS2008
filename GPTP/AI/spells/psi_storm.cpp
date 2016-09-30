#include "spells.h"
#include <AI/ai_common.h>

//V241 for VS2008

namespace AI {

	class PsiStormTargetFinderProc: public scbw::UnitFinderCallbackMatchInterface {

	  private:
		CUnit* caster;
		bool isUnderAttack;

	  public:
		PsiStormTargetFinderProc(CUnit* caster, bool isUnderAttack)
		  : caster(caster), isUnderAttack(isUnderAttack) {}

		bool match(CUnit* target) {

			if (!isTargetWorthHitting(target, caster))
			  return false;

			if (!scbw::canWeaponTargetUnit(WeaponId::PsiStorm, target, caster))
			  return false;

			const int totalEnemyLife = getTotalEnemyLifeInArea(target->getX(), target->getY(), 96, caster, WeaponId::PsiStorm);
			if (!isUnderAttack && totalEnemyLife < 250)
			  return false;

			const int totalAllyLife = getTotalAllyLifeInArea(target->getX(), target->getY(), 96, caster, WeaponId::PsiStorm);
			if (totalAllyLife * 2 >= totalEnemyLife)
			  return false;

			return true;

		}
	};

	CUnit* findBestPsiStormTarget(CUnit* caster, bool isUnderAttack) {

	  int bounds;

	  if (isUnderAttack)
		bounds = 32 * 9;
	  else if (isUmsMode(caster->playerId))
		bounds = 32 * 64;
	  else
		bounds = 32 * 32;


	  return scbw::UnitFinder::getNearestTarget(
		caster->getX() - bounds, caster->getY() - bounds,
		caster->getX() + bounds, caster->getY() + bounds,
		caster, PsiStormTargetFinderProc(caster,isUnderAttack));
	}

} //AI
