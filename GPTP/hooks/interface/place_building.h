#pragma once
#include <SCBW/scbwdata.h>
#include <SCBW/enumerations.h>
#include <SCBW/api.h>

namespace hooks {

void placebuildingRefineryCheck(CUnit* unit);						//0048E1E0	placebuildingRefineryCheck
void doPlacebuildingChecking(CUnit* unit);							//0048E210  doPlacebuildingChecking
void placebuildingNormalProc();										//0048E490  placebuildingNormalProc
void pracebuildingProc();											//0048E6E0  pracebuildingProc
void issuePlacebuildingOrder(u8 buildOrderId, u32 unitToBuildId);	//0048E730  issuePlacebuildingOrder

void injectPlaceBuildingHooks();

} //namespace hooks 
