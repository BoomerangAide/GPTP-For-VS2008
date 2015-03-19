#pragma once
#include "../SCBW/structures/CUnit.h"

namespace hooks {

	bool isInfestableUnit(const CUnit *unit);
	bool unitCanInfest(const CUnit *unit);

	//Both units must exist, so normally for internal use only
	//But the code is there to be modded
	void orderMorphIntoInfested(CUnit *unitInfested, CUnit *unitInfesting);

	//The injector function that should be called in initialize.cpp
	void injectInfestationHooks();

} //hooks
