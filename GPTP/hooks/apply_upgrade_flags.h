

//Header file for the Apply Upgrade Flags hook module.
#pragma once
#include <SCBW/structures.h>

//V241 for VS2008

namespace hooks {

void applyUpgradeFlagsToNewUnitHook(CUnit *unit);
void applyUpgradeFlagsToExistingUnitsHook(u8 playerId, u8 upgradeId);

void injectApplyUpgradeFlags();

//Wrapper for the native version of applyUpgradeFlagsToExistingUnits().
//Applies @upgradeId to all units that are owned by the owner of @p unit.
void applyUpgradeFlagsToExistingUnits(CUnit *unit, u8 upgradeId);

} //hooks
