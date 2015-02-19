//Header file for the Tech Target Check hook module.
#include <SCBW/structures/CUnit.h>

//V241 for VS2008

namespace hooks {

//The hook function injected into StarCraft
u16 getTechUseErrorMessageHook(const CUnit *target, u8 castingPlayer, u16 techId);

//The injector function that should be called in initialize.cpp
void injectTechTargetCheckHooks();

//Native callable version of the hook
u16 getTechUseErrorMessage(const CUnit *target, u8 castingPlayer, u16 techId);

} //hooks
