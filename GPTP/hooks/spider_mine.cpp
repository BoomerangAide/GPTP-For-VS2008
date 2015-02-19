#include "spider_mine.h"
#include <SCBW/api.h>
#include <SCBW/enumerations.h>
#include <SCBW/UnitFinder.h>

//V241 for VS2008

//Helper class for findBestSpiderMineTargetHook()
class SpiderMineTargetFinder: public scbw::UnitFinderCallbackMatchInterface {

  const CUnit *spiderMine;

  public:
    //Check if @p unit is a suitable target for the @p spiderMine.
    bool match(const CUnit *target) {

		//Don't attack friendly / allied units
		if (!spiderMine->isTargetEnemy(target))
		  return false;

		//Don't attack invincible units / air units / buildings
		using UnitStatus::Invincible;
		using UnitStatus::InAir;
		using UnitStatus::GroundedBuilding;
		if (target->status & (Invincible | InAir | GroundedBuilding))
		  return false;

		//Don't attack hovering units
		if (units_dat::MovementFlags[target->id] == (0x01 | 0x40 | 0x80))  //Note: This is not a mistake; SC actually uses a "==" comparison to check flags (I know it's a WTF).
		  return false;

		return true;

    }

    //Constructor
    SpiderMineTargetFinder(const CUnit *spiderMine) : spiderMine(spiderMine) {}
};

namespace hooks {

//Return the best target for the Spider Mine. If there is no suitable target,
//return NULL instead.
CUnit* findBestSpiderMineTargetHook(const CUnit *spiderMine) {
  //Default StarCraft behavior

  //Don't search for a target if the spider mine is under a Disruption Web
  if (spiderMine->status & UnitStatus::CanNotAttack)
    return NULL;

  s32 range = 32 * spiderMine->getSeekRange();
  
  return scbw::UnitFinder::getNearestTarget(
    spiderMine->getX() - range, spiderMine->getY() - range,
    spiderMine->getX() + range, spiderMine->getY() + range,
    spiderMine, SpiderMineTargetFinder(spiderMine));
}

//Return the initial burrowing delay time (in frames) for the Spider Mine.
u8 getSpiderMineBurrowTimeHook(const CUnit *spiderMine) {
  //Default StarCraft behavior
  return 60;
}

} //hooks
