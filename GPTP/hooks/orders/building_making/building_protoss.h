#pragma once
#include "../../../SCBW/structures/CUnit.h"

namespace hooks {

	void orders_ProbeBuild(CUnit* unit);	//004E4D00
	void orders_BuildSelf2(CUnit* building);//004E4F40

	void injectBuildingProtossHooks();

} //hooks