//Header file for the Transfer Tech & Upgrades hook module.
#include <SCBW/structures/CUnit.h>

namespace hooks {

void transferUnitTechToPlayerHook(CUnit* sourceUnit, u8 targetPlayerId, u32 researchTechFunc = 0x0047B3C0);	//0x004E2C00

//Default value for researchUpgradesFunc is set as increaseUpgradeLevel @ 0047B340
//The other possible value is sub_47B940 @ 0047B940 (called by GiveAllUnitPropertiesToPlayerAndMakeIdle)
void transferUnitUpgradesToPlayerHook(CUnit* sourceUnit, u8 targetPlayerId, u32 researchUpgradesFunc = 0x0047B340);		//0x004E2B50

void injectTransferTechAndUpgradesHooks();

} //hooks
