#include <AI/ai_common.h>

//V241 for VS2008

namespace AI {

bool AI_spellcasterHook(CUnit *unit, bool isUnitBeingAttacked);

} //AI

namespace hooks {

void injectSpellcasterAI();

} //hooks