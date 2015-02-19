#include <SCBW/structures/CUnit.h>

namespace hooks {

const char* getWeaponTooltipString(u8 weaponId, const CUnit *unit);
const char* getArmorTooltipString(const CUnit *unit);
const char* getShieldTooltipString(const CUnit *unit);
const char* getSpecialTooltipString(u16 iconUnitId, const CUnit *unit);

void injectUnitTooltipHook();

} //hooks
