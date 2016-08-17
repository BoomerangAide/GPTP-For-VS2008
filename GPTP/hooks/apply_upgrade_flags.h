

//Header file for the Apply Upgrade Flags hook module.
#pragma once
#include <SCBW/structures.h>

namespace hooks {

void applyUpgradeFlagsToNewUnitHook(CUnit* unit);
void applyUpgradeFlagsToExistingUnitsHook(CUnit* unit, u8 upgradeId);

void injectApplyUpgradeFlags();

//Wrapper for the native version of applyUpgradeFlagsToExistingUnits().
//Applies @upgradeId to all units that are owned by the owner of @p unit.
void applyUpgradeFlagsToExistingUnits(CUnit* unit, u8 upgradeId);

} //hooks
