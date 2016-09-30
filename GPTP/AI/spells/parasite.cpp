#include "spells.h"
#include <AI/ai_common.h>

//V241 for VS2008

namespace AI {

	class ParasiteTargetFinderProc: public scbw::UnitFinderCallbackMatchInterface {

	  private:
		CUnit* caster;

	  public:
		ParasiteTargetFinderProc(CUnit* caster)
		  : caster(caster) {}

		bool match(CUnit* target) {

			if (!isTargetWorthHitting(target, caster))
			  return false;

			if (isUmsMode(caster->playerId) && target->parasiteFlags)
			  return false;

			if (target->parasiteFlags & (1 << caster->playerId))
			  return false;

			if (!scbw::canWeaponTargetUnit(WeaponId::Parasite, target, caster))
			  return false;

			if (target->canDetect())
			  return true;

			if (!(target->status & UnitStatus::IsHallucination)
				&& (target->id != UnitId::overlord || scbw::getUpgradeLevel(target->playerId, UpgradeId::VentralSacs))
				&& units_dat::SpaceProvided[target->id] > 0)
			  return true;

			if (target->isValidCaster())
			  return true;

			if (units_dat::BaseProperty[target->id] & UnitProperty::Worker)
			  return true;

			if (target->getCurrentLifeInGame() >= 300)
			  return true;

			return false;

		}
	};

	CUnit* findBestParasiteTarget(CUnit* caster, bool isUnderAttack) {

	  int bounds;

	  if (isUnderAttack)
		bounds = 32 * 9;
	  else
		bounds = 32 * 64;

	  return scbw::UnitFinder::getNearestTarget(
		caster->getX() - bounds, caster->getY() - bounds,
		caster->getX() + bounds, caster->getY() + bounds,
		caster, ParasiteTargetFinderProc(caster));
	}


} //AI
