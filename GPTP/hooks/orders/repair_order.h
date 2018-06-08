#pragma once
#include "../../SCBW/structures/CUnit.h"

namespace hooks {

	void orders_Repair1(CUnit* unit);		//004673D0

	void injectRepairOrderHook();

} //hooks