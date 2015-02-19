#pragma once
#include "../SCBW/structures/CUnit.h"

// V241 for VS2008

namespace hooks {

bool unitCanDetectHook(const CUnit *unit);
u32 getCloakedTargetVisibility(const CUnit *unit, const CUnit* target);

void injectDetectorHooks();

} //hooks
