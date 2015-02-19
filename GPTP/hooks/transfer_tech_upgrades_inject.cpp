//Injector source file for the Transfer Tech & Upgrades hook module.
#include "transfer_tech_upgrades.h"
#include <hook_tools.h>

namespace {

void __declspec(naked) transferUnitTechToPlayerWrapper() {
  static const CUnit *source;
  static u8 targetPlayerId;
  __asm {
    PUSHAD
    MOV source, EBX
    MOV AL, [ESP + 40]   ;// (PUSHAD saves 32) + (CALL saves 4) + 4 == 40
    MOV targetPlayerId, AL
    MOV EBP, ESP
  }

  hooks::transferUnitTechToPlayerHook(source, targetPlayerId);

  __asm {
    POPAD
    RETN 8
  }
}

void __declspec(naked) transferUnitUpgradesToPlayerWrapper() {
  static const CUnit *source;
  static u8 targetPlayerId;
  __asm {
    PUSHAD
    MOV source, EBX
    MOV AL, [ESP + 40]   ;// (PUSHAD saves 32) + (CALL saves 4) + 4 == 40
    MOV targetPlayerId, AL
    MOV EBP, ESP
  }

  hooks::transferUnitUpgradesToPlayerHook(source, targetPlayerId);

  __asm {
    POPAD
    RETN 8
  }
}

void __declspec(naked) applyUnitUpgradeFlagsToAllFriendlyUnitsWrapper() {
  static CUnit *unit;
  __asm {
    PUSHAD
    MOV unit, EBX
    MOV EBP, ESP
  }

  hooks::applyUnitUpgradeFlagsToAllFriendlyUnitsHook(unit);

  __asm {
    POPAD
    RETN 8
  }
}

} //Unnamed namespace

namespace hooks {

void injectTransferTechAndUpgradesHooks() {
  callPatch(transferUnitTechToPlayerWrapper, 0x0047CA04);
  callPatch(transferUnitUpgradesToPlayerWrapper, 0x0047CA0F);
  callPatch(applyUnitUpgradeFlagsToAllFriendlyUnitsWrapper, 0x0047CABD);
}

} //hooks
