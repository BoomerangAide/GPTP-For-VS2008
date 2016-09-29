#pragma once
#include "../../../SCBW/structures/CUnit.h"

namespace hooks {

void orders_TerranBuildSelf(CUnit* building);		//00467760
void orders_SCVBuild2(CUnit* unit);					//00467A70
void orders_SCVBuild(CUnit* unit);					//00467FD0

void injectBuildingTerranHook();

} //hooks