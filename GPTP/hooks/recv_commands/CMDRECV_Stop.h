#pragma once
#include "../../SCBW/structures/CUnit.h"

namespace hooks {

void CMDRECV_ReaverStop();			//004C1240
void CMDRECV_CarrierStop();			//004C1430
void CMDRECV_Stop(u8 bCommandType);	//004C2190

void injectCMDRECV_StopHooks();

} //hooks
