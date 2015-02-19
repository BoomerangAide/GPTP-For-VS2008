//Contains hooks that control unit movement speed, acceleration, and turn speed.

#include "unit_speed.h"
#include "../SCBW/enumerations.h"
#include "../SCBW/scbwdata.h"

//V241 for VS2008

namespace hooks {

/// Calculates the unit's modified movement speed, factoring in upgrades and status effects.
///
/// @return		The modified speed value.
u32 getModifiedUnitSpeedHook(const CUnit* unit, u32 baseSpeed) {
	//Default StarCraft behavior
	u32 speed = baseSpeed;
	int speedModifier = (unit->stimTimer ? 1 : 0) - (unit->ensnareTimer ? 1 : 0)
                      + (unit->status & UnitStatus::SpeedUpgrade ? 1 : 0);
	if (speedModifier > 0) {
		if (unit->id == UnitId::scout || unit->id == UnitId::Hero_Mojo || unit->id == UnitId::Hero_Artanis)
      speed = 1707;
		else {
			speed += speed >> 1;
			if (speed < 853)
        speed = 853;
		}
	}
	else if (speedModifier < 0)
		speed >>= 1;
	return speed;
}

/// Calculates the unit's acceleration, factoring in upgrades and status effects.
///
/// @return		The modified acceleration value.
u32 getModifiedUnitAccelerationHook(const CUnit* unit) {
	//Default StarCraft behavior
	u32 acceleration = flingy_dat::Acceleration[units_dat::Graphic[unit->id]];
	int modifier = (unit->stimTimer ? 1 : 0) - (unit->ensnareTimer ? 1 : 0)
                 + (unit->status & UnitStatus::SpeedUpgrade ? 1 : 0);
	if (modifier > 0)
		acceleration <<= 1;
	else if (modifier < 0)
		acceleration -= acceleration >> 2;
	return acceleration;
}

/// Calculates the unit's turn speed, factoring in upgrades and status effects.
///
/// @return		The modified turning speed value.
u32 getModifiedUnitTurnSpeedHook(const CUnit* unit) {
	//Default StarCraft behavior
	u32 turnSpeed = flingy_dat::TurnSpeed[units_dat::Graphic[unit->id]];
	int modifier = (unit->stimTimer ? 1 : 0) - (unit->ensnareTimer ? 1 : 0)
                 + (unit->status & UnitStatus::SpeedUpgrade ? 1 : 0);
	if (modifier > 0)
		turnSpeed <<= 1;
	else if (modifier < 0)
		turnSpeed -= turnSpeed >> 2;
	return turnSpeed;
}

} //hooks
