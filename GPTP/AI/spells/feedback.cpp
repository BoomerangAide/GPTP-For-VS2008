#include "spells.h"
#include <AI/ai_common.h>

// V241 for VS2008

namespace AI {

class FeedbackTargetFinderProc: public scbw::UnitFinderCallbackMatchInterface {
  private:
    CUnit* caster;

  public:
    FeedbackTargetFinderProc(CUnit* caster)
      : caster(caster) {}

    bool match(CUnit* target) {

		if (!isTargetWorthHitting(target, caster))
		  return false;

		if (!target->isValidCaster())
		  return false;

		if (target->status & UnitStatus::GroundedBuilding)
		  return false;

		if (units_dat::BaseProperty[target->id] & UnitProperty::Hero)
		  return false;

		if (target->energy / 256u >= target->getCurrentLifeInGame())
		  return true;

		return false;

    }
};

CUnit* findBestFeedbackTarget(CUnit* caster, bool isUnderAttack) {

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
    caster, FeedbackTargetFinderProc(caster));
}

} //AI
