#pragma once
#include <SCBW/structures/CUnit.h>

namespace hooks {

u32 getSightRangeHook(const CUnit *unit, bool isForSpellCasting);

void injectSightRangeHook();

} //hooks
