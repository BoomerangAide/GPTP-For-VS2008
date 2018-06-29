#pragma once
#include "../../SCBW/structures/CUnit.h"

namespace hooks {

bool CMDRECV_PlaceBuildingAllowed(CUnit* builder, u8 orderId, u16 builtUnitId);	//0048DBD0
void cmdRECV_PlaceBuildingNormal(s16 x, s16 y, u32 orderId, u32 builtUnitId);	//0048E010
void cmdRECV_PlaceBuildingAddon(s16 x, s16 y, u32 orderId, u32 builtUnitId);	//0048E0A0
void CMDRECV_Build(u8 orderId, s16 x, s16 y, u16 builtUnitId);					//004C23C0

void injectCMDRECV_BuildHooks();

} //hooks
