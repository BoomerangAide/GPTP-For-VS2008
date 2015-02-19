#include "update_status_effects.h"
#include "../hook_tools.h"

//V241 for VS2008

namespace {

const u32 Hook_UpdateStatusEffects = 0x00492F70;

//Inject with jmpPatch()
void __declspec(naked) updateStatusEffectsWrapper() {
  CUnit *unit;

  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV unit, EAX
  }

  hooks::updateStatusEffectsHook(unit);

  __asm {
    POPAD
    RETN
  }
}

} //unnamed namespace

namespace hooks {

void injectUpdateStatusEffects() {
  jmpPatch(updateStatusEffectsWrapper, Hook_UpdateStatusEffects);
}

void updateStatusEffects(CUnit *unit) {
  __asm {
    PUSHAD
    MOV EAX, unit
    CALL Hook_UpdateStatusEffects
    POPAD
  }
}

} //hooks
