#include <SCBW/structures/CUnit.h>

namespace hooks {

bool unitCanMorphHook(CUnit* unit, u16 morphUnitId);
bool isEggUnitHook(u16 unitId);
bool isRallyableEggUnitHook(u16 unitId);
u16 getUnitMorphEggTypeHook(u16 unitId);
u16 getCancelMorphRevertTypeHook(CUnit* eggUnit);
s16 getUnitVerticalOffsetOnBirth(CUnit* unit);
bool hasSuppliesForUnitHook(u8 playerId, u16 unitId, bool canShowErrorMessage);

void injectUnitMorphHooks();

} //hooks
