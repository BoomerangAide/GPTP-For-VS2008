#include <AI/ai_common.h>

namespace AI {

bool AI_spellcasterHook(CUnit* unit, bool isUnitBeingAttacked);

} //AI

namespace hooks {

void injectSpellcasterAI();

} //hooks