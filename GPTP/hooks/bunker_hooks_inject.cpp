#include "bunker_hooks.h"
#include "../hook_tools.h"

//V241 for VS2008

namespace {

const u32 Hook_UnitCanAttackInsideBunkerYes = 0x004790DC;
void __declspec(naked) unitCanAttackInsideBunkerWrapper() {
  CUnit *unit;
  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV unit, ESI
  }

  if (hooks::unitCanAttackInsideBunkerHook(unit)) {
    __asm {
      POPAD
      JMP Hook_UnitCanAttackInsideBunkerYes
    }
  }
  else {
    __asm {
      POPAD
      POP ESI   ;//Code at 0x00479147
      RETN
    }
  }
}

void __declspec(naked) createBunkerAttackThingyWrapper() {
  static CUnit *unit;
  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV unit, EAX
  }

  hooks::createBunkerAttackThingyHook(unit);

  __asm {
    POPAD
    RETN
  }
}



} //unnamed namespace

namespace hooks {

void injectBunkerHooks() {
  jmpPatch(unitCanAttackInsideBunkerWrapper, 0x004790A3);
  callPatch(createBunkerAttackThingyWrapper, 0x00478CAF);
}

} //hooks