#include "sight_range.h"
#include <hook_tools.h>

extern const u32 Func_GetSightRange;  //Defined in CUnit.cpp

namespace {

void __declspec(naked) getSightRangeWrapper() {
  static CUnit *unit;
  static Bool32 isForSpellCasting;
  static u32 sightRange;

  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV unit, EDX
    MOV EAX, DWORD PTR [EBP + 36]
    MOV isForSpellCasting, EAX
  }

  sightRange = hooks::getSightRangeHook(unit, isForSpellCasting != 0);

  __asm {
    MOV EAX, sightRange
    MOV [ESP + 28], EAX
    POPAD
    RETN 4
  }
}

} //unnamed namespace

namespace hooks {

void injectSightRangeHook() {
  jmpPatch(getSightRangeWrapper, Func_GetSightRange);
}

} //hooks
