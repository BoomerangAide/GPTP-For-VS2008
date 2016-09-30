#include "spellcasting.h"
#include <hook_tools.h>

namespace {

void __declspec(naked) AI_spellcasterWrapper() {

  static CUnit* unit;
  static Bool32 isUnderAttack;
  static Bool32 result;

  __asm {
    PUSH EBP
    MOV EBP, ESP
    MOV unit, EAX
	MOV EAX, [EBP+0x08]
    MOV isUnderAttack, EAX
	PUSHAD
  }

  if(AI::AI_spellcasterHook(unit, isUnderAttack != 0))
	  result = 1;
  else
	  result = 0;

  __asm {
    POPAD
    MOV EAX, result
	POP EBP
    RETN 4
  }
}

} //unnamed namespace

namespace hooks {

void injectSpellcasterAI() {
  jmpPatch(AI_spellcasterWrapper, 0x004A13C0, 2);
}

} //AI
