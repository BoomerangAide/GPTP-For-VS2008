//Header file for the Weapon Fire hook module.
#include <SCBW/structures/CUnit.h>

namespace hooks {

void fireWeaponHook(CUnit* unit, u8 weaponId);

void injectWeaponFireHooks();

} //hooks
