//Injector source file for the Apply Upgrade Flags hook module.
#include "apply_upgrade_flags.h"
#include <hook_tools.h>

//V241 for VS2008

namespace {

void __declspec(naked) applyUpgradeFlagsToNewUnitWrapper() {
  static CUnit *unit;
  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV unit, ESI
  }

  hooks::applyUpgradeFlagsToNewUnitHook(unit);

  __asm {
    POPAD
    RETN
  }
}

void __declspec(naked) applyUpgradeFlagsToExistingUnitsWrapper() {
  static CUnit *unit;
  static u8 upgradeId;
  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV ECX, [EBP + 36]  ;//8 - 4 + 32
    MOV unit, ECX
    MOV upgradeId, AL
  }

  hooks::applyUpgradeFlagsToExistingUnitsHook(unit->playerId, upgradeId);

  __asm {
    POPAD
    RETN 4
  }
}

} //Unnamed namespace

namespace hooks {

const u32 Hook_ApplyUpgradeFlagsToExistingUnits = 0x00454540;

void injectApplyUpgradeFlags() {
  jmpPatch(applyUpgradeFlagsToNewUnitWrapper, 0x00454370);
  jmpPatch(applyUpgradeFlagsToExistingUnitsWrapper, Hook_ApplyUpgradeFlagsToExistingUnits);
}

void applyUpgradeFlagsToExistingUnits(CUnit *unit, u8 upgradeId) {
  __asm {
    PUSHAD
    PUSH unit
    MOV AL, upgradeId
    CALL Hook_ApplyUpgradeFlagsToExistingUnits
    POPAD
  }
}

} //hooks