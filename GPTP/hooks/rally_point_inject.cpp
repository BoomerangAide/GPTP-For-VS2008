#include "rally_point.h"
#include "../hook_tools.h"

namespace {

const u32 Hook_SetRallyGenericJmpBack1 = 0x00456384;
const u32 Hook_SetRallyGenericJmpBack2 = 0x0049AD77;

//Inject with jmpPatch()
const u32 Hook_OrderNewUnitToRally = 0x00466F62;
const u32 Hook_OrderNewUnitToRallyBack = 0x00466FA3;
void __declspec(naked) orderNewUnitToRallyWrapper() {
  static CUnit *unit, *factory;
  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV unit, ESI
    MOV factory, ECX
  }

  hooks::orderNewUnitToRally(unit, factory);

  __asm {
    POPAD
    JMP Hook_OrderNewUnitToRallyBack
  }
}

//Inject with callPatch()
const u32 Hook_SetRallyPosition_Call      = 0x00456083;
void __declspec(naked) setRallyPositionWrapper_Call() {
  static CUnit *unit;
  static u16 x, y;
  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV unit, EAX
    MOV y, DI
    MOV x, DX
  }

  hooks::setRallyPosition(unit, x, y);

  __asm {
    POPAD
    RETN 8
  }
}

//Inject with jmpPatch()
const u32 Hook_SetRallyPosition_Jmp1      = 0x00456256;
void __declspec(naked) setRallyPositionWrapper_Jmp1() {
  static CUnit *unit;
  static u16 x, y;
  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV unit, EDI
    MOV x, BX
    MOV y, SI
  }

  hooks::setRallyPosition(unit, x, y);

  __asm {
    POPAD
    JMP Hook_SetRallyGenericJmpBack1
  }
}

//Inject with jmpPatch()
const u32 Hook_SetRallyPosition_Jmp2      = 0x0049ACEF;
void __declspec(naked) setRallyPositionWrapper_Jmp2() {
  static CUnit *unit;
  static u16 x, y;
  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV unit, ESI
    MOV x, CX
    MOV y, DX
  }

  hooks::setRallyPosition(unit, x, y);

  __asm {
    POPAD
    JMP Hook_SetRallyGenericJmpBack2
  }
}

//Inject with callPatch()
const u32 Hook_SetRallyUnit_Call          = 0x0045605F;
void __declspec(naked) setRallyUnitWrapper_Call() {
  static CUnit *unit, *target;
  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV unit, ECX
    MOV target, EAX
  }

  hooks::setRallyUnit(unit, target);

  __asm {
    POPAD
    RETN
  }
}

//Inject with jmpPatch()
const u32 Hook_SetRallyUnit_Jmp1          = 0x0045620D;
void __declspec(naked) setRallyUnitWrapper_Jmp1() {
  static CUnit *unit, *target;
  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV unit, EDI
    MOV target, EAX
  }

  hooks::setRallyUnit(unit, target);

  __asm {
    POPAD
    JMP Hook_SetRallyGenericJmpBack1
  }
}

//Inject with jmpPatch()
const u32 Hook_SetRallyUnit_Jmp2          = 0x0049ACB0;
void __declspec(naked) setRallyUnitWrapper_Jmp2() {
  static CUnit *unit, *target;
  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV unit, ESI
    MOV target, EBX
  }

  hooks::setRallyUnit(unit, target);

  __asm {
    POPAD
    JMP Hook_SetRallyGenericJmpBack2
  }
}

} //unnamed namespace

namespace hooks {

void injectRallyHooks() {
  jmpPatch(orderNewUnitToRallyWrapper,    Hook_OrderNewUnitToRally);
  callPatch(setRallyPositionWrapper_Call, Hook_SetRallyPosition_Call);
  jmpPatch(setRallyPositionWrapper_Jmp1,  Hook_SetRallyPosition_Jmp1);
  jmpPatch(setRallyPositionWrapper_Jmp2,  Hook_SetRallyPosition_Jmp2);
  callPatch(setRallyUnitWrapper_Call,     Hook_SetRallyUnit_Call);
  jmpPatch(setRallyUnitWrapper_Jmp1,      Hook_SetRallyUnit_Jmp1);
  jmpPatch(setRallyUnitWrapper_Jmp2,      Hook_SetRallyUnit_Jmp2);
}

} //hooks
