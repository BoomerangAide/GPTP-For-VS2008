#pragma once
#include "../../SCBW/structures/CUnit.h"

namespace hooks {

void CMDRECV_TrainFighter();		//004C1800
void CMDRECV_Train(u16 wUnitType);	//004C1C20

void injectTrainCmdRecvHooks();

} //hooks
