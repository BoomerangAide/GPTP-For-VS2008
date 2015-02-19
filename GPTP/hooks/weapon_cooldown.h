#pragma once
#include "../SCBW/structures.h"

//V241 for VS2008

namespace hooks {

u32 getModifiedWeaponCooldownHook(const CUnit* unit, u8 weaponId);

void injectWeaponCooldownHook();

} //hooks