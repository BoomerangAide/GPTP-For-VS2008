#pragma once
#include "../../SCBW/structures/CUnit.h"

namespace hooks {

	void orders_MedicHeal2(CUnit* unit);			//00463740
	void orders_HealMove(CUnit* unit);				//004637B0
	void orders_Medic(CUnit* unit);					//00463900
	//void orders_MedicHoldPosition(CUnit* unit);	//base_orders/stopholdpos_orders.h
	void orders_MedicHeal1(CUnit* unit);			//00464180

	void injectMedicOrdersHooks();

} //hooks