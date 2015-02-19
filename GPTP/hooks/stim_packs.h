#pragma once
#include "../SCBW/structures/CUnit.h"

//V241 for VS2008

namespace hooks {

void useStimPacksHook(CUnit *unit);
bool canUseStimPacksHook(const CUnit *unit);

void injectStimPacksHooks();

} //hooks
