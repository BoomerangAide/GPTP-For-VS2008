#pragma once
#include "../../SCBW/structures/CUnit.h"

namespace hooks {

bool unit_IsStandardAndMovable(CUnit* unit);	//0047B770
CUnit* getActivePlayerFirstSelection();			//0049A850

void injectUtilsHooks();

} //hooks