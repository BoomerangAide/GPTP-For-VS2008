#pragma once
#include "../../SCBW/structures/CUnit.h"

namespace hooks {

	void function_0046FB40(CUnit* clicked_unit);
	u32 SortAllUnits(CUnit* unit,CUnit** unit_list,CUnit** units_in_bounds);

	void injectSelectMod();

}
