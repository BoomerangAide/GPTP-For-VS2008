#pragma once
#include "../../SCBW/structures/CUnit.h"

namespace hooks {

	void orders_BuildingLand(CUnit* unit);
	void orders_BuildingLiftoff(CUnit* unit);

	//The injector function that should be called in initialize.cpp
	void injectLiftLandHooks();

} //hooks
