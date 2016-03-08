#pragma once
#include "../SCBW/structures/CUnit.h"

namespace hooks {

u8 getCloakingTech(const CUnit *unit);

Bool32 BTNSCOND_IsCloaked(CUnit* unit, u32 playerId, u16 reqVar);	//0x00429210
Bool32 BTNSCOND_CanCloak(CUnit* unit, u32 playerId, u16 reqVar);	//0x004292C0

void injectCloakingTechHooks();

} //hooks
