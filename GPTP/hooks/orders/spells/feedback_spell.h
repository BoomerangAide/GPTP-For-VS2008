#pragma once
#include "../../../SCBW/structures/CUnit.h"

namespace hooks {

	void orders_Feedback(CUnit* unit);	//0x004F6D40

	void injectFeedbackSpellHook();

} //hooks