#include "spells.h"
#include <AI/ai_common.h>

// V241 for VS2008

namespace AI {

class DisruptionWebTargetFinderProc: public scbw::UnitFinderCallbackMatchInterface {

  private:
    CUnit* caster;

  public:
    DisruptionWebTargetFinderProc(CUnit* caster)
      : caster(caster) {}

    bool match(CUnit* target) {

		if (!isTargetWorthHitting(target, caster))
		  return false;

		CUnit* targetOfTarget;
		if (target->id == UnitId::bunker && target->hasLoadedUnit()) {
		  targetOfTarget = target->getFirstLoadedUnit()->orderTarget.unit;
		}
		else
		  targetOfTarget = target->orderTarget.unit;

		if (!targetOfTarget || targetOfTarget->playerId >= 8)
		  return false;

		if (!(targetOfTarget->status & UnitStatus::InAir))
		  return false;

		if (caster->isTargetEnemy(targetOfTarget))
		  return false;

		if (target->status & UnitStatus::CanNotAttack)
		  return false;

		if (!(target->status & UnitStatus::InAir)
			&& caster->getDistanceToTarget(target) <= 32 * 8)
		  return true;

		if (target->id == UnitId::missile_turret
			|| target->id == UnitId::bunker
			|| target->id == UnitId::spore_colony
			|| target->id == UnitId::photon_cannon)
		  return true;

		return false;

    }
};

CUnit* findBestDisruptionWebTarget(CUnit* caster, bool isUnderAttack) {
  int bounds;
  if (isUnderAttack)
    bounds = 32 * 9;
  else if (isUmsMode(caster->playerId))
    bounds = 32 * 128;
  else
    bounds = 32 * 64;

  return scbw::UnitFinder::getNearestTarget(
    caster->getX() - bounds, caster->getY() - bounds,
    caster->getX() + bounds, caster->getY() + bounds,
    caster, DisruptionWebTargetFinderProc(caster));
}

} //AI