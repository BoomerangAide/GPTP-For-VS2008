//Header file for the Transfer Tech & Upgrades hook module.
#include <SCBW/structures/CUnit.h>

//V241 for VS2008

namespace hooks {

void transferUnitTechToPlayerHook(const CUnit *source, u8 targetPlayerId);
void transferUnitUpgradesToPlayerHook(const CUnit *source, u8 targetPlayerId);
void applyUnitUpgradeFlagsToAllFriendlyUnitsHook(CUnit *unit);

void injectTransferTechAndUpgradesHooks();

} //hooks
