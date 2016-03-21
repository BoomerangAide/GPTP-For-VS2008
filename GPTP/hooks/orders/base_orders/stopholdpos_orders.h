#pragma once
#include "../../../SCBW/structures/CUnit.h"

namespace hooks {

	void orders_MedicHoldPosition(CUnit* unit);		//00464050  orders_MedicHoldPosition
	void orders_ReaverStop(CUnit* unit);			//004654B0  orders_ReaverStop
	void orders_Guard(CUnit* unit);					//00475B90  orders_Guard
	void function_004774A0(CUnit* unit);			//004774A0	sub_4774A0_unreferenced
	void orders_TurretGuard(CUnit* unit);			//004777F0  orders_TurretGuard

	void injectStopHoldPosOrdersHooks();

} //namespace hooks
