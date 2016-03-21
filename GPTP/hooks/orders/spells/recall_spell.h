#pragma once
#include "../../../SCBW/structures/CUnit.h"

namespace hooks {

	void spells_Recall_ActionOnValidTargetForRecall(CUnit* target, CUnit* caster);	//004942D0  sub_4942D0
	void spells_Recall_ActionOnTargetInRange(CUnit* target, CUnit* caster);			//00494400  sub_494400
	void orders_Recall(CUnit* unit);												//00494470

	void injectRecallSpellHooks();

} //hooks
