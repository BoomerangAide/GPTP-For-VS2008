#include "spells.h"
#include <AI/ai_common.h>

//V241 for VS2008

namespace AI {

	class NukeLaunchTargetFinderProc: public scbw::UnitFinderCallbackMatchInterface {

	  private:
		CUnit* caster;

	  public:
		NukeLaunchTargetFinderProc(CUnit* caster)
		  : caster(caster) {}

		bool match(CUnit* target) {

			if ((target->status & (UnitStatus::Cloaked | UnitStatus::RequiresDetection))
				&& !target->isVisibleTo(caster->playerId))
			  return false;

			if (!caster->isTargetEnemy(target))
			  return false;

			const int totalEnemyClumpValue = getTotalEnemyNukeValueInArea(target->getX(), target->getY(), 192, caster);
			if (totalEnemyClumpValue >= 800)
			  return true;

			return false;

		}
	};

	CUnit* findBestNukeLaunchTarget(CUnit* caster, bool isUnderAttack) {
	  return scbw::UnitFinder::getNearestTarget(caster, NukeLaunchTargetFinderProc(caster));
	}

} //AI
