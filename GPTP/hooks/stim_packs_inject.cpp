#include "stim_packs.h"
#include "../hook_tools.h"

namespace {

//Inject with callPatch
const u32 Hook_UseStimPacksAi         = 0x00440148;
void __declspec(naked) useStimPacksAiWrapper() {
  CUnit *unit;

  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV unit, EAX
  }

  hooks::useStimPacksHook(unit);

  __asm {
    POPAD
    RETN
  }
}

//Inject with jmpPatch
const u32 Hook_UseStimPacksPlayer     = 0x004C2F68;
const u32 Hook_UseStimPacksPlayerBack = 0x004C2FF9;
void __declspec(naked) useStimPacksPlayerWrapper() {
  CUnit *unit;

  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV unit, ESI
  }

  hooks::useStimPacksHook(unit);

  __asm {
    POPAD
    JMP Hook_UseStimPacksPlayerBack
  }
}

//Inject with jmpPatch
const u32 Hook_CanUseStimPacks        = 0x004234E6;
const u32 Hook_CanUseStimPacksYes     = 0x00423528;
const u32 Hook_CanUseStimPacksNo      = 0x004234EB;
void __declspec(naked) canUseStimPacksWrapper() {
  CUnit *unit;

  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV unit, EAX
  }

  if (hooks::canUseStimPacksHook(unit)) {
    __asm {
      POPAD
      JMP Hook_CanUseStimPacksYes
    }
  }
  else {
    __asm {
      POPAD
      JMP Hook_CanUseStimPacksNo
    }

  }
}

} //unnamed namespace

namespace hooks {

void injectStimPacksHooks() {
  callPatch(useStimPacksAiWrapper,    Hook_UseStimPacksAi);
  jmpPatch(useStimPacksPlayerWrapper, Hook_UseStimPacksPlayer);
  jmpPatch(canUseStimPacksWrapper,    Hook_CanUseStimPacks);
}

} //hooks
