#pragma once
#include <SCBW/structures/CUnit.h>

//V241 for VS2008

namespace hooks {

u8 getArmorBonusHook(const CUnit *unit);

void injectArmorBonusHook();

} //hooks
