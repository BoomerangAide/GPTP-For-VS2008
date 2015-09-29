#pragma once
#include "../../SCBW/structures/CUnit.h"

namespace hooks {

	void function_0049D660(CUnit* main_building);					//0x0049D660
	bool function_004E8C80(CUnit* unit, CUnit* main_building);		//0x004E8C80
	void secondaryOrd_SpawningLarva(CUnit* unit);					//0x004EA780
	void secondaryOrd_SpreadCreepSpawningLarva(CUnit* unit);		//0x004EA880

	//The injector function that should be called in initialize.cpp
	void injectLarvaCreepSpawnHooks();

} //hooks
