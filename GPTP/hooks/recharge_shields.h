#pragma once
#include "../SCBW/structures/CUnit.h"

namespace hooks {

bool unitCanRechargeShieldsHook(const CUnit *target, const CUnit *battery);
void orderRechargeShieldsHook(CUnit *unit);

void injectRechargeShieldsHooks();

} //hooks
