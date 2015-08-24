#include "spellcasting.h"
#include <hook_tools.h>

namespace {

void __declspec(naked) AI_spellcasterWrapper() {
  static CUnit *unit;
  static u32 isUnderAttack;
  static bool result;

  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV unit, EAX
    MOV EBX, [ESP + 36]   ;// (PUSHAD saves 32) + (CALL saves 4) == 36
    MOV isUnderAttack, EBX
  }

  result = AI::AI_spellcasterHook(unit, isUnderAttack != 0);

  __asm {
    POPAD
    MOVZX EAX, result
    RETN 4
  }
}

} //unnamed namespace

namespace hooks {

void injectSpellcasterAI() {
  jmpPatch(AI_spellcasterWrapper, 0x004A13C0);
}

} //AI
