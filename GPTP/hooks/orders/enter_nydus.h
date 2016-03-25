#pragma once
#include "../../SCBW/structures/CUnit.h"

namespace hooks {

	bool canEnterNydusCanal(CUnit* unit, CUnit* nydusCanal);		//004E8C20
	void enterNydusCanal_Effect(CUnit* unit, CUnit* nydusCanal);	//004EA180
	void orders_EnterNydusCanal(CUnit* unit);						//004EA3E0

	void injectEnterNydusHooks();

} //hooks
