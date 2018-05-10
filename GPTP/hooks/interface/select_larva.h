#pragma once
#include "../../SCBW/structures/CUnit.h"

namespace hooks {

	u32 getLarvaeUnitsFromList(CUnit** unitList, CUnit** outputList);	//00423190
	void BTNSACT_SelectLarva();											//00423930

	void injectSelectLarvaHooks();

}