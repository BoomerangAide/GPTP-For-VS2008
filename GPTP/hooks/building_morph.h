#include <SCBW/structures/CUnit.h>

//V241 for VS2008

namespace hooks {

bool isMorphedBuildingHook(u16 unitId);
int getMorphBuildingTypeCountHook(const CUnit *unit, u16 unitId, bool ignoreIncomplete);

void injectBuildingMorphHooks();

} //hooks
