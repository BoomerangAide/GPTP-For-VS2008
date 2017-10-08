#pragma once
#include "../../SCBW/structures/CUnit.h"

namespace hooks {

void CMDRECV_MergeDarkArchon();	//004C0CD0
void CMDRECV_MergeArchon();		//004C0E90

void injectCMDRECV_MergeArchonHooks();

} //hooks
