#pragma once
#include "../../SCBW/structures.h"

namespace AI {

	CUnit* harvestNextNearestResourcesEx(CUnit* mineral_field, CUnit* worker, u16 x, u16 y);
	CUnit* FindMineralField(u32 unk_resource_area);

}

namespace hooks {
	
	//The injector function that should be called in initialize.cpp
	void injectAI_HarvestHooks();

} //hooks
