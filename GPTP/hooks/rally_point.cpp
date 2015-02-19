//Contains hooks that control how rally points are used.

#include "rally_point.h"
#include "../SCBW/scbwdata.h"
#include "../SCBW/enumerations.h"
#include "../SCBW/api.h"

namespace hooks {

/// Orders newly-produced units to rally, based upon the properties of the
/// building that produced it.
///
/// @param  unit      The unit that needs to receive rally orders.
/// @param  factory   The unit (building) that created the given unit.
void orderNewUnitToRally(CUnit* unit, CUnit* factory) {
  //Default StarCraft behavior

  //Do nothing if the rally target is the factory itself or the rally target position is 0
  if (factory->rally.unit == factory || !(factory->rally.pt.x)) return;

  //Following should be allowed only on friendly units
  if (factory->rally.unit && factory->rally.unit->playerId == unit->playerId)
    unit->orderTo(OrderId::Follow, factory->rally.unit);
  else
    unit->orderTo(OrderId::Move, factory->rally.pt.x, factory->rally.pt.y);
}

/// Called when the player sets the rally point on the ground.
void setRallyPosition(CUnit *unit, u16 x, u16 y) {
  //Default StarCraft behavior
  unit->rally.unit = NULL;
  unit->rally.pt.x = x;
  unit->rally.pt.y = y;
}

/// Called when the player sets the rally point on a unit.
void setRallyUnit(CUnit *unit, CUnit *target) {
  //Default StarCraft behavior
  if (!target) target = unit;
  unit->rally.unit = target;
  unit->rally.pt.x = target->getX();
  unit->rally.pt.y = target->getY();
}

} //hooks