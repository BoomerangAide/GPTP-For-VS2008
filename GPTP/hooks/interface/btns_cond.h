#pragma once
#include "../../SCBW/structures/CUnit.h"

namespace hooks {

s32 BTNSCOND_NoNydusExit(CUnit* unit);		//00428340
s32 BTNSCOND_Movement(CUnit* unit);		//004283C0
s32 BTNSCOND_HasScarabs(CUnit* unit);		//004286A0

//The injector function that should be called in initialize.cpp
void injectBtnsCondHook();

} //hooks