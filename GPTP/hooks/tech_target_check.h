//Header file for the Tech Target Check hook module.
#include <SCBW/structures/CUnit.h>

namespace hooks {

//The hook function injected into StarCraft
u16 getTechUseErrorMessageHook(CUnit* target, u8 castingPlayer, u16 techId);

//The injector function that should be called in initialize.cpp
void injectTechTargetCheckHooks();

} //hooks
