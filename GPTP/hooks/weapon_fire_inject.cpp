//Injector source file for the Weapon Fire hook module.
#include "weapon_fire.h"
#include <hook_tools.h>

namespace {

void __declspec(naked) fireWeaponWrapper() {
  static CUnit *unit;
  static u8 weaponId;

  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV AL, [ESP + 36]   ;// (PUSHAD saves 32) + (CALL saves 4) == 36
    MOV weaponId, AL
    MOV unit, ESI
  }

  hooks::fireWeaponHook(unit, weaponId);

  __asm {
    POPAD
    RETN 4
  }
}

} //Unnamed namespace

extern const u32 Func_FireUnitWeapon;

namespace hooks {

void injectWeaponFireHooks() {
  jmpPatch(fireWeaponWrapper, Func_FireUnitWeapon);
}

} //hooks
