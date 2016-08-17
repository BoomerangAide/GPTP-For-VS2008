#pragma once
#include "../SCBW/structures/CUnit.h"

namespace hooks {

void setRallyUnit(CUnit* unit, CUnit* target);			//0x00466B40
void orderNewUnitToRally(CUnit* unit, CUnit* factory);	//0x00466F50
void setRallyPosition(CUnit* unit, u16 x, u16 y);		//0x00466910

void injectRallyHooks();

} //hooks
