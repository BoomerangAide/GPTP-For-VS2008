#include "spells.h"
#include <AI/ai_common.h>

//V241 for VS2008

namespace AI {

	class YamatoGunTargetFinderProc: public scbw::UnitFinderCallbackMatchInterface {

	  private:
		CUnit* caster;

	  public:
		YamatoGunTargetFinderProc(CUnit* caster)
		  : caster(caster) {}

		bool match(CUnit* target) {
			if (!isTargetWorthHitting(target, caster))
			  return false;

			if ((target->status & UnitStatus::GroundedBuilding) && target->hasWeapon())
			  return true;

			if (target->id == UnitId::bunker && target->hasLoadedUnit())
			  return true;

			if (target->id == UnitId::egg)
			  return false;

			const int targetLife = target->getCurrentLifeInGame();
			if (200 <= targetLife && targetLife <= 450
				&& !(units_dat::BaseProperty[target->id] & UnitProperty::Hero))
			  return true;

			return false;
		}
	};

	CUnit* findBestYamatoGunTarget(CUnit* caster, bool isUnderAttack) {

	  if (isUnderAttack) {
		int bounds = 32 * 16;
		return scbw::UnitFinder::getNearestTarget(
		  caster->getX() - bounds, caster->getY() - bounds,
		  caster->getX() + bounds, caster->getY() + bounds,
		  caster, YamatoGunTargetFinderProc(caster));
	  }
	  else {
		return scbw::UnitFinder::getNearestTarget(caster, YamatoGunTargetFinderProc(caster));
	  }
	}

} //AI
