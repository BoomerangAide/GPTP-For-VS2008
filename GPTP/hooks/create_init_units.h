#pragma once
#include "../SCBW/structures/CUnit.h"

namespace hooks {

void CreateInitialMeleeBuildings(u8 raceId, u32 playerId);	//0049D7C0
void CreateInitialMeleeUnits();								//0049DA40
void CreateInitialOverlord(u8 playerId);					//0049D6C0

void injectCreateInitUnitsHooks();

} //hooks