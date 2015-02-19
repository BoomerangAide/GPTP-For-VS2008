#pragma once
#include "../SCBW/structures/CUnit.h"

//V241 for VS2008

namespace hooks {

u8 getCloakingTech(const CUnit *unit);

void injectCloakingTechHooks();

} //hooks
