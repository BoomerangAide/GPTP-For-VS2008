#pragma once
#include "../../../SCBW/structures/CUnit.h"

namespace hooks {

	void secondaryOrd_TrainFighter(CUnit* unit);	//00466790
	void function_00468420(CUnit* unit);			//00468420

	void injectUnitTrainHooks();

} //hooks