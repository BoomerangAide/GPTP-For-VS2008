#pragma once
#include "../../SCBW/structures/CUnit.h"

namespace hooks {

void CMDRECV_CancelNuke();				//004BFCD0
void CMDRECV_CancelAddon();				//004BFF30
void CMDRECV_CancelUpgrade();			//004BFFC0
void CMDRECV_CancelResearch();			//004C0070
void CMDRECV_CancelTrain(u16 wUnitID);	//004C0100
void CMDRECV_CancelUnitMorph();			//004C2EC0
void CMDRECV_CancelConstruction();		//004C2EF0

void injectCMDRECV_CancelHooks();

} //hooks
