#include "attack_priority.h"
#include <hook_tools.h>

namespace {

const u32 Hook_GetAttackPriority = 0x00442160;
//Inject with jmpPatch()
void __declspec(naked) getAttackPriorityWrapper() {
  static CUnit *target, *attacker;
  static u32 result;

  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV target, EDI
    MOV attacker, EBX
  }

  result = hooks::getAttackPriorityHook(target, attacker);

  __asm {
    POPAD
    MOV EAX, result
    RETN
  }
}

const u32 Hook_FindBestAttackTarget = 0x00443080;
//Inject with jmpPatch()
void __declspec(naked) findBestAttackTargetWrapper() {
  static CUnit *unit;
  static const CUnit *target;

  __asm {
    PUSHAD
    MOV unit, EAX
  }

  target = hooks::findBestAttackTargetHook(unit);

  __asm {
    POPAD
    MOV EAX, target
    RETN
  }
}

const u32 Hook_FindRandomAttackTarget = 0x00442FC0;
//Inject with jmpPatch()
void __declspec(naked) findRandomAttackTargetWrapper() {
  static CUnit *unit;
  static const CUnit *target;

  __asm {
    PUSHAD
    MOV unit, ESI
  }

  target = hooks::findRandomAttackTargetHook(unit);

  __asm {
    POPAD
    MOV EAX, target
    RETN
  }
}

} //unnamed namespace

namespace hooks {

void injectAttackPriorityHooks() {
  jmpPatch(getAttackPriorityWrapper,      Hook_GetAttackPriority);
  jmpPatch(findBestAttackTargetWrapper,   Hook_FindBestAttackTarget);
  jmpPatch(findRandomAttackTargetWrapper, Hook_FindRandomAttackTarget);
}

} //hooks

