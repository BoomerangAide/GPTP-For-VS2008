#pragma once
#include "../SCBW/structures/CUnit.h"

namespace hooks {

	bool isInfestableUnit(const CUnit *unit);
	bool unitCanInfest(const CUnit *unit);

	//infestation order used by infestation victim
	void orderMorphIntoInfested(CUnit *unitInfested);

	//infestation order used by the unit that infest
	void orderInfestTarget(CUnit *unitInfesting);

} //hooks
