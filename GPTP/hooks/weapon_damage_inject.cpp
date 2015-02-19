#include "weapon_damage.h"
#include "../hook_tools.h"

//V241 for VS2008

extern const u32 Func_DoWeaponDamage; //Defined in CUnit.cpp

namespace {

//Inject with JmpPatch
void __declspec(naked) weaponDamageWrapper() {
  static CUnit *target, *attacker;
  static s32 damage;
  static u8 weaponId, damageDivisor, attackingPlayer;
  static s8 direction;

  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV damage, EAX
    MOV target, EDI
    MOV EBX, [ESP + 36]   ;// (PUSHAD saves 32) + (CALL saves 4) == 36
    MOV weaponId, BL      ;// Use EBX as a "temp" variable for copying args
    MOV EBX, [ESP + 40]
    MOV damageDivisor, BL
    MOV EBX, [ESP + 44]
    MOV direction, BL
    MOV EBX, [ESP + 48]
    MOV attacker, EBX
    MOV EBX, [ESP + 52]
    MOV attackingPlayer, BL
  }

  hooks::weaponDamageHook(damage, target, weaponId, attacker, attackingPlayer,
                          direction, damageDivisor);

  __asm {
    POPAD
    RETN 20
  }
}

} //unnamed namespace

namespace hooks {

void injectWeaponDamageHook() {
  jmpPatch(weaponDamageWrapper, Func_DoWeaponDamage);
}

} //hooks
