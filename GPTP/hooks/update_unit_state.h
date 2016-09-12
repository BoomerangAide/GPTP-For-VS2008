#pragma once
#include <SCBW/structures/CUnit.h>

namespace hooks {

void updateUnitEnergy(CUnit* unit);		//0x004EB4B0
void updateUnitStateHook(CUnit* unit);	//0x004EC290

void injectUpdateUnitState();

} //hooks
