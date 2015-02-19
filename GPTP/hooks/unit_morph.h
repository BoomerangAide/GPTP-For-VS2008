#include <SCBW/structures/CUnit.h>

namespace hooks {

bool unitCanMorphHook(const CUnit *unit, u16 morphUnitId);
bool isEggUnitHook(u16 unitId);
bool isRallyableEggUnitHook(u16 unitId);
u16 getUnitMorphEggTypeHook(u16 unitId);
u16 getCancelMorphRevertTypeHook(const CUnit *eggUnit);
s16 getUnitVerticalOffsetOnBirth(const CUnit *unit);
bool hasSuppliesForUnitHook(u8 playerId, u16 unitId, bool canShowErrorMessage);

void injectUnitMorphHooks();

} //hooks
