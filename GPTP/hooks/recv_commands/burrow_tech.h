#pragma once
#include "../../SCBW/structures/CUnit.h"

namespace hooks {

void CMDRECV_Unburrow();				//004C1AC0
void CMDRECV_Burrow(u8 bCommandType);	//004C1FA0
void Unburrow_Proc(CUnit* unit);		//004E97C0

void injectBurrowTechHooks();

} //hooks
