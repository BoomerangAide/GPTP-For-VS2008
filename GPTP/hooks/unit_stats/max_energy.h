#pragma once
#include <SCBW/structures/CUnit.h>

namespace hooks {

u16 getUnitMaxEnergyHook(CUnit* const unit);

void injectUnitMaxEnergyHook();

} //hooks
