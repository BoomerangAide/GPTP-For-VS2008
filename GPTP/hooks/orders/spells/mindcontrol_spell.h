#pragma once
#include "../../../SCBW/structures/CUnit.h"

namespace hooks {

	void ordersCastMindControl(CUnit* unit);	//004F6950

	void injectMindControlSpellHook();

} //hooks