#pragma once
#include <SCBW/structures/CUnit.h>

namespace hooks {

u16 getUnitMaxEnergyHook(const CUnit* const unit);

void injectUnitMaxEnergyHook();

} //hooks
