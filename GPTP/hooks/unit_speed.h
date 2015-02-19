#pragma once
#include "../SCBW/structures/CUnit.h"

namespace hooks {

u32 getModifiedUnitSpeedHook(const CUnit* unit, u32 baseSpeed);
u32 getModifiedUnitAccelerationHook(const CUnit* unit);
u32 getModifiedUnitTurnSpeedHook(const CUnit* unit);

void injectUnitSpeedHooks();

} //hooks
