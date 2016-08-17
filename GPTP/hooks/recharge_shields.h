#pragma once
#include "../SCBW/structures/CUnit.h"

namespace hooks {

Bool32 unitCanRechargeShieldsHook(CUnit* target, CUnit* battery);
void orderRechargeShieldsHook(CUnit* unit);

void injectRechargeShieldsHooks();

} //hooks
