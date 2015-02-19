#include "cloak_nearby_units.h"
#include <SCBW/UnitFinder.h>
#include <SCBW/enumerations.h>
#include <SCBW/api.h>
#include <algorithm>

//V241 for VS2008

//Helper functions
namespace {

void secondaryOrder_Cloak(CUnit *unit);
} //unnamed namespace

class cloakNearbyUnitProc : public scbw::UnitFinderCallbackProcInterface {

	public:
		cloakNearbyUnitProc(CUnit *cloaker, u32 cloakRadius, bool needsRefresh) : 
		  cloaker(cloaker), cloakRadius(cloakRadius), needsRefresh(needsRefresh) {}

		  void proc(CUnit *unit) {
			//Don't cloak fellow Arbiters and Nukes
			if (unit->id == UnitId::arbiter
				|| unit->id == UnitId::danimoth
				|| unit->id == UnitId::nuclear_missile)
			  return;

			//Don't cloak buildings and doodad units (?)
			if (units_dat::BaseProperty[unit->id] & (UnitProperty::Building | UnitProperty::NeutralAccessories))
			  return;

			//Don't cloak hallucinations
			if (unit->status & UnitStatus::IsHallucination)
			  return;

			//Not sure. Perhaps to prevent warping-in units and buildings from being cloaked?
			if (unit->mainOrderId == OrderId::Warpin)
			  return;

			//Only cloak units owned by the same player
			if (cloaker->playerId != unit->playerId)
			  return;

			//Distance check
			if (cloaker->getDistanceToTarget(unit) <= cloakRadius) {
			  secondaryOrder_Cloak(unit);
			  //Remove energy cost for units that use energy to cloak
			  if (!(unit->status & UnitStatus::CloakingForFree)) {
				unit->status |= UnitStatus::CloakingForFree;
				needsRefresh = true;
			  }
			}
		  }

	private:
		CUnit *cloaker;
		u32 cloakRadius;
		bool needsRefresh;

};

namespace hooks {

//Cloak all units near @p cloaker.
void cloakNearbyUnitsHook(CUnit *cloaker) {
  //Default StarCraft behavior

  //Use the unit's air weapon range
  u32 cloakRadius = cloaker->getMaxWeaponRange(cloaker->getAirWeapon());

  //Run the unit finder
  scbw::UnitFinder unitsToCloak(
    cloaker->getX() - cloakRadius, cloaker->getY() - cloakRadius,
    cloaker->getX() + cloakRadius, cloaker->getY() + cloakRadius);

  bool needsRefresh = false;

  unitsToCloak.forEach(cloakNearbyUnitProc(cloaker,cloakRadius,needsRefresh));

  if (needsRefresh)
    scbw::refreshConsole();
}

} //hooks

/**** Helper function definitions. Do not change anything below this! ****/

namespace {

void secondaryOrder_Cloak(CUnit *unit) {
  CUnit** const firstBurrowedUnit = (CUnit**) 0x0063FF5C;

  if (unit->isCloaked++)
    return;

  if (unit->status & UnitStatus::RequiresDetection)
    return;

  if (unit->burrow_link.next)
    return;
  
  unit->burrow_link.next = *firstBurrowedUnit;
  unit->burrow_link.prev = NULL;
  if (*firstBurrowedUnit)
    (*firstBurrowedUnit)->burrow_link.prev = unit;
  *firstBurrowedUnit = unit;

  scbw::refreshConsole();
}

} //unnamed namespace
