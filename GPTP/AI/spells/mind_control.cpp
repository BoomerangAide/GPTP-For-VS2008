#include "spells.h"
#include <AI/ai_common.h>

//V241 for VS2008

namespace AI {

	class MindControlTargetFinderProc: public scbw::UnitFinderCallbackMatchInterface {
	  private:
		CUnit* caster;

	  public:
		MindControlTargetFinderProc(CUnit* caster)
		  : caster(caster) {}

		bool match(CUnit* target) {

			if (!isTargetWorthHitting(target, caster))
			  return false;

			if (units_dat::BaseProperty[target->id] & UnitProperty::Hero)
			  return false;

			if (target->id == UnitId::shuttle || target->id == UnitId::dropship)
			  if (target->hasLoadedUnit())
				return true;

			switch (target->id) {
			  case UnitId::shuttle:
			  case UnitId::dropship:
				if (target->hasLoadedUnit())
				  return true;
				break;

			  case UnitId::siege_tank:
			  case UnitId::siege_tank_s:
			  case UnitId::science_vessel:
			  case UnitId::battlecruiser:
			  case UnitId::medic:
			  case UnitId::overlord:
			  case UnitId::ultralisk:
			  case UnitId::queen:
			  case UnitId::defiler:
			  case UnitId::devourer:
			  case UnitId::dark_archon:
			  case UnitId::high_templar:
			  case UnitId::arbiter:
			  case UnitId::carrier:
			  case UnitId::reaver:
			  case UnitId::lurker:
				return true;

			  default:
				if (units_dat::MineralCost[target->id] >= units_dat::MineralCost[UnitId::dark_templar]
					&& units_dat::GasCost[target->id] >= units_dat::GasCost[UnitId::dark_templar])
				  return true;
				break;
			}

			return false;
		}
	};


CUnit* findBestMindControlTarget(CUnit* caster, bool isUnderAttack) {

  int bounds = 32 * 32;

  return scbw::UnitFinder::getNearestTarget(
    caster->getX() - bounds, caster->getY() - bounds,
    caster->getX() + bounds, caster->getY() + bounds,
    caster, MindControlTargetFinderProc(caster));
}

} //AI
