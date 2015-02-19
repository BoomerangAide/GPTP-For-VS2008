//Injector source file for the Tech Target Check hook module.
#include "tech_target_check.h"
#include <hook_tools.h>

//V241 for VS2008

namespace {

const u32 Func_GetTechUseErrorMessage = 0x00491E80;

void __declspec(naked) getTechUseErrorMessageWrapper() {
  static CUnit *target;
  static u8 castingPlayer;
  static u16 techId;
  static u16 errorMessage;

  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV target, EAX
    MOV castingPlayer, BL
    MOV EAX, [ESP + 36]   ;// (PUSHAD saves 32) + (CALL saves 4) == 36
    MOV techId, AX
  }

  errorMessage = hooks::getTechUseErrorMessageHook(target, castingPlayer, techId);

  __asm {
    POPAD
    MOV AX, errorMessage
    RETN 4
  }
}

} //Unnamed namespace

namespace hooks {

void injectTechTargetCheckHooks() {
  jmpPatch(getTechUseErrorMessageWrapper, Func_GetTechUseErrorMessage);
}

u16 getTechUseErrorMessage(const CUnit *target, u8 castingPlayer, u16 techId) {
  u32 techId_ = techId;
  static u16 errorMessage;

  __asm {
    PUSHAD
    PUSH techId_
    MOV BL, castingPlayer
    MOV EAX, target
    CALL Func_GetTechUseErrorMessage
    MOV errorMessage, AX
    POPAD
  }

  return errorMessage;
}

} //hooks
