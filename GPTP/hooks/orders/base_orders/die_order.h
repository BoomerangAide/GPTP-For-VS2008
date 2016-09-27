#pragma once
#include "../../../SCBW/structures/CUnit.h"

namespace hooks {

void orders_Die(CUnit* unit);		//00479480

void injectDieOrderHook();

} //hooks