#pragma once
#include <SCBW/structures/CUnit.h>

//V241 for VS2008

namespace hooks {

void updateStatusEffectsHook(CUnit *unit);

void injectUpdateStatusEffects();

//Wrapper for native version of updateStatusEffects()
void updateStatusEffects(CUnit *unit);

} //hooks