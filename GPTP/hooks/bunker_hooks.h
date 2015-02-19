#pragma once
#include "../SCBW/structures/CUnit.h"

//V241 for VS2008

namespace hooks {

bool unitCanAttackInsideBunkerHook(const CUnit *unit);
void createBunkerAttackThingyHook(const CUnit *unit);

void injectBunkerHooks();

} //hooks
