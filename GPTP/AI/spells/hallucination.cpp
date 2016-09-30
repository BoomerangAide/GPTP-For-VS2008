#include "spells.h"
#include <AI/ai_common.h>

//V241 for VS2008

namespace AI {

class HallucinationTargetFinderProc: public scbw::UnitFinderCallbackMatchInterface {

  private:
    CUnit* caster;

  public:
    HallucinationTargetFinderProc(CUnit* caster)
      : caster(caster) {}

    bool match(CUnit* target) {

		if (target->playerId != caster->playerId)
		  return false;

		if (target->status & UnitStatus::Invincible)
		  return false;

		if (scbw::getTechUseErrorMessage((CUnit*)target, caster->playerId, TechId::Hallucination) != 0)
		  return false;

		if (target->id == UnitId::carrier
			|| target->id == UnitId::scout
			|| target->id == UnitId::arbiter
			|| target->id == UnitId::archon)
		  return true;

		return false;

    }
};

CUnit* findBestHallucinationTarget(CUnit* caster, bool isUnderAttack) {

  if (isUnderAttack)
    return NULL;

  int bounds = 32 * 32;

  return scbw::UnitFinder::getNearestTarget(
    caster->getX() - bounds, caster->getY() - bounds,
    caster->getX() + bounds, caster->getY() + bounds,
    caster, HallucinationTargetFinderProc(caster));
}

} //AI
