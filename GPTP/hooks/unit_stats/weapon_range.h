#pragma once
#include <SCBW/structures/CUnit.h>

namespace hooks {

u8 getSeekRangeHook(const CUnit *unit);
u32 getMaxWeaponRangeHook(const CUnit *unit, u8 weaponId);

void injectWeaponRangeHooks();

} //hooks
