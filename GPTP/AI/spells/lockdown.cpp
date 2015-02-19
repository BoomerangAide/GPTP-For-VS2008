#include "spells.h"
#include <AI/ai_common.h>

//V241 for VS2008

namespace AI {

	class LockdownFinderProc: public scbw::UnitFinderCallbackMatchInterface {
	  private:
		const CUnit *caster;

	  public:
		LockdownFinderProc(const CUnit *caster)
		  : caster(caster) {}

		bool match(const CUnit *target) {

			if (!isTargetWorthHitting(target, caster))
			  return false;

			if (!scbw::canWeaponTargetUnit(WeaponId::Lockdown, target, caster))
			  return false;

			if (target->isFrozen())
			  return false;

			if (target->id == UnitId::dropship || target->id == UnitId::shuttle) {
			  if (target->movementFlags & 0x2 && target->hasLoadedUnit())
				return true;
			}

			if (target->id == UnitId::carrier || target->id == UnitId::reaver)
			  return true;

			if (isTargetAttackingAlly(target, caster))
			  return true;

			return false;

		}
	};

	CUnit* findBestLockdownTarget(const CUnit *caster, bool isUnderAttack) {

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
		caster, LockdownFinderProc(caster));
	}

} //AI
