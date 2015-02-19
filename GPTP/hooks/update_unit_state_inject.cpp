#include "update_unit_state.h"
#include <hook_tools.h>

namespace {

//Inject with jmpPatch()
const u32 Hook_UpdateUnitState = 0x004EC290;
void __declspec(naked) updateUnitStateWrapper() {
  CUnit *unit;

  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV unit, EAX
  }

  hooks::updateUnitStateHook(unit);

  __asm {
    POPAD
    RETN
  }
}

} //unnamed namespace

namespace hooks {

void injectUpdateUnitState() {
  jmpPatch(updateUnitStateWrapper, Hook_UpdateUnitState);
}

} //hooks
