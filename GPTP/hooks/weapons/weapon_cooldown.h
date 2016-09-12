#pragma once
#include "../../SCBW/structures.h"

namespace hooks {

u32 getModifiedWeaponCooldownHook(CUnit* unit, u8 weaponId);

void injectWeaponCooldownHook();

} //hooks
