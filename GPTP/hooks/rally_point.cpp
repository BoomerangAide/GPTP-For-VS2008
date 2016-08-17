//Contains hooks that control how rally points are used.

#include "rally_point.h"
#include "../SCBW/api.h"

namespace hooks {

/// Orders newly-produced units to rally, based upon the properties of the
/// building that produced it.
///
/// @param  unit      The unit that needs to receive rally orders.
/// @param  factory   The unit (building) that created the given unit.
///
/// Identical to sub_466F50 @ 00466F50

void orderNewUnitToRally(CUnit* unit, CUnit* factory) {

	//Do nothing if the rally target is the factory itself or the rally target position is 0
	if (
		factory != NULL && 
		factory->isFactory() && 
		factory->rally.unit != factory && 
		factory->rally.pt.x != 0
	)
	{

		//Following should be allowed only on friendly units
		if (factory->rally.unit != NULL && (factory->rally.unit)->playerId == unit->playerId)
			unit->orderTo(OrderId::Follow, factory->rally.unit);
		else
			unit->orderTo(OrderId::Move, factory->rally.pt.x, factory->rally.pt.y);

	}

}

;

/// Called when the player sets the rally point on the ground.
void setRallyPosition(CUnit* unit, u16 x, u16 y) {
	unit->rally.unit = NULL;
	unit->rally.pt.x = x;
	unit->rally.pt.y = y;
}

;

/// Called when the player sets the rally point on a unit.
void setRallyUnit(CUnit* unit, CUnit* target) {

	if (target == NULL) 
		target = unit;

	unit->rally.unit = target;
	unit->rally.pt.x = target->getX();
	unit->rally.pt.y = target->getY();

}

;

} //hooks
