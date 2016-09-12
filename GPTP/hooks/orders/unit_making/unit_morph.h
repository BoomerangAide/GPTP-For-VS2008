#pragma once
#include "../../../SCBW/structures/CUnit.h"

namespace hooks {

	void orders_ZergBirth(CUnit* unit);	//0x0045DD60
	void orders_Morph1(CUnit* unit);	//0x0045DEA0

	void injectUnitMorphHooks();

} //hooks