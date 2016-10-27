#pragma once
#include "../../SCBW/structures/CUnit.h"

namespace hooks {

	void orders_Pickup1(CUnit* unit);		//004E7300
	void orders_Pickup3_0(CUnit* unit);		//004E73B0
	void orders_Pickup2(CUnit* unit);		//004E75D0
	void orders_MoveUnload(CUnit* unit);	//004E7700
	void orders_Pickup4_0(CUnit* unit);		//004E7B70
	void orders_EnterTransport(CUnit* unit);//004E7CF0
	void orders_Unload(CUnit* unit);		//004E80D0

	void injectLoadUnloadOrdersHooks();

} //hooks