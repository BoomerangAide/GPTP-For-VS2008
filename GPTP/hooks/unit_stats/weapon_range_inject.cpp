#include "weapon_range.h"
#include <hook_tools.h>

namespace {

//Inject with jmpPatch()
void __declspec(naked) getSeekRangeWrapper() {
  CUnit *unit;
  u8 seekRange;
  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV unit, EDX
  }

  seekRange = hooks::getSeekRangeHook(unit);

  __asm {
    MOVZX EAX, seekRange
    MOV [ESP + 28], EAX
    POPAD
    RETN
  }
}

//Inject with jmpPatch()
void __declspec(naked) getMaxWeaponRangeWrapper() {
  CUnit *unit;
  u8 weaponId;
  u32 maxWeaponRange;
  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV unit, EAX
    MOV weaponId, BL
  }

  maxWeaponRange = hooks::getMaxWeaponRangeHook(unit, weaponId);

  __asm {
    MOV EAX, maxWeaponRange;
    MOV [ESP + 28], EAX
    POPAD
    RETN
  }
}

} //unnamed namespace

//Defined in SCBW/structures/CUnit.cpp
extern const u32 Func_GetMaxWeaponRange;
extern const u32 Func_GetSeekRange;

namespace hooks {

void injectWeaponRangeHooks() {
  jmpPatch(getSeekRangeWrapper,       Func_GetSeekRange);
  jmpPatch(getMaxWeaponRangeWrapper,  Func_GetMaxWeaponRange);
}

} //hooks
