#include "recharge_shields.h"
#include "../hook_tools.h"

namespace {

//Inject with jmpPatch
const u32 Hook_UnitCanRechargeShields = 0x00493520;
void __declspec(naked) unitCanRechargeShieldsWrapper() {
  CUnit *target, *battery;
  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV battery, EDI
    MOV target, EAX
  }

  if (hooks::unitCanRechargeShieldsHook(target, battery)) {
    __asm {
      POPAD
      MOV EAX, 1
      RETN
    }
  }
  else {
    __asm {
      POPAD
      XOR EAX, EAX  ;//Identical to MOV EAX, 0
      RETN
    }
  }
}

//Inject with callPatch
void __declspec(naked) orderRechargeShieldsWrapper() {
  static CUnit *unit;
  __asm {
    PUSHAD
    MOV unit, EDI
  }

  hooks::orderRechargeShieldsHook(unit);

  __asm {
    POPAD
    RETN
  }
}

} //unnamed namespace

namespace hooks {

void injectRechargeShieldsHooks() {
  jmpPatch(unitCanRechargeShieldsWrapper, Hook_UnitCanRechargeShields);
  callPatch(orderRechargeShieldsWrapper,  0x004EC637);
}

} //hooks