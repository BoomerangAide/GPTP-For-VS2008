#pragma once
#include <SCBW/structures/CUnit.h>

namespace hooks {

u32 getSightRangeHook(CUnit* unit, bool isForSpellCasting);

void injectSightRangeHook();

} //hooks
