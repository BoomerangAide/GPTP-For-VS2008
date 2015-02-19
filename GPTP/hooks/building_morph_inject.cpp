#include "building_morph.h"
#include <hook_tools.h>
#include <SCBW/api.h>
#include <algorithm>

//V241 for VS2008

namespace {

//-------- isMorphingBuilding() --------//

void __declspec(naked) isRemorphingBuildingWrapper() {
  static CUnit *unit;
  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV unit, EAX
  }

  if (!(unit->status & UnitStatus::Completed)
      && hooks::isMorphedBuildingHook(unit->buildQueue[unit->buildQueueSlot]))
  {
    __asm {
      POPAD
      MOV EAX, 1
      RETN
    }
  }
  else {
    __asm {
      POPAD
      XOR EAX, EAX  ;//Set EAX to 0
      RETN
    }
  }
}

//-------- UnitStatAct_ProgressBarIconText --------//

const u32 Hook_IsMorphedBuilding_ConsoleProgressBarTextBack = 0x00426B74;
void __declspec(naked) isMorphedBuildingWrapper_ConsoleProgressBarText() {
  static const CUnit *unit;
  static u16 tblErrorMessage;
  __asm {
    PUSHAD
    MOV EBP, ESP
  }

  unit = *activePortraitUnit;
  if (unit->status & UnitStatus::GroundedBuilding && unit->isFrozen())
  {
    tblErrorMessage = 828;    //<6>Disabled<0>
  }
  else {
    u16 unitId = unit->buildQueue[unit->buildQueueSlot];
    if (unit->status & UnitStatus::Completed
        || !hooks::isMorphedBuildingHook(unitId))
      unitId = unit->id;

    if (unitId == UnitId::gateway || unitId == UnitId::stargate)
      tblErrorMessage = 771;  //Morphing<0>, Building<0>, Opening Warp Gate<0>
    else
      tblErrorMessage = 774;  //Morphing<0>, Building<0>, Building<0>
  }

  __asm {
    POPAD
    MOV ECX, unit
    MOVZX EDX, tblErrorMessage
    JMP Hook_IsMorphedBuilding_ConsoleProgressBarTextBack
  }
}

//-------- AI_MorphBehavior() --------//

const u32 Hook_AI_MorphBehavior_IsMorphedBuildingYes = 0x0043508B;
void __declspec(naked) isMorphedBuildingWrapper_AI_MorphBehavior() {
  static u16 buildUnitId;
  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV buildUnitId, DI
  }

  if (hooks::isMorphedBuildingHook(buildUnitId)) {
    __asm {
      POPAD
      JMP Hook_AI_MorphBehavior_IsMorphedBuildingYes
    }
  }
  else {  //Code at 0x00435122
    __asm {
      POPAD
      POP EDI
      XOR EAX, EAX
      POP ESI
      POP EBP
      RETN 8
    }
  }
}

//-------- statdata_UnitWireframeUpdate() --------//

const u32 Hook_IsMorphedBuilding_ConsoleWireframeUpdateBack = 0x00456955;
void __declspec(naked) isMorphedBuildingWrapper_ConsoleWireFrameUpdate() {
  static CUnit *unit;
  static u16 buildUnitId;
  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV unit, ESI
  }

  buildUnitId = unit->buildQueue[unit->buildQueueSlot];
  if (unit->status & UnitStatus::Completed
      || !hooks::isMorphedBuildingHook(buildUnitId))
    buildUnitId = unit->id;

  __asm {
    POPAD
    MOVZX ECX, buildUnitId
    JMP Hook_IsMorphedBuilding_ConsoleWireframeUpdateBack
  }
}

//-------- orders_ZergBuildSelf() --------//

const u32 Hook_isMorphedBuilding_ZergBuildSelf_GetTypeBack = 0x0045D53F;
void __declspec(naked) isMorphedBuildingWrapper_ZergBuildSelf_GetType() {
  static CUnit *unit;
  static u16 buildUnitId;
  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV unit, EDI
  }

  buildUnitId = unit->buildQueue[unit->buildQueueSlot];
  if (!hooks::isMorphedBuildingHook(buildUnitId))
    buildUnitId = unit->id;

  __asm {
    POPAD
    MOVZX EBX, buildUnitId
    JMP Hook_isMorphedBuilding_ZergBuildSelf_GetTypeBack
  }
}

void __declspec(naked) isMorphedBuildingWrapper_ZergBuildSelf_Complete() {
  static u16 unitId;
  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV unitId, AX
  }

  if (hooks::isMorphedBuildingHook(unitId)) {
    __asm {
      POPAD
      MOV EAX, 1
      RETN
    }
  }
  else {
    __asm {
      POPAD
      XOR EAX, EAX  ;//Set EAX to 0
      RETN
    }
  }
}

//This was moved out of the naked function to prevent stack corruption bug
void zergBuildSelf_UpdateBuildTimerAndHp(CUnit *unit, u16 unitId) {
  bool isOperationCwalEnabled = scbw::isCheatEnabled(CheatFlags::OperationCwal);
  if (unit->remainingBuildTime) {
    if (isOperationCwalEnabled)
      unit->remainingBuildTime -= std::min<u16>(unit->remainingBuildTime, 16);
    else
      unit->remainingBuildTime--;
  }
  if (!hooks::isMorphedBuildingHook(unitId)) {
    u32 hpGain = unit->buildRepairHpGain;
    if (isOperationCwalEnabled)
      hpGain *= 16;
    unit->setHp(unit->hitPoints + hpGain);
  }
}

void __declspec(naked) isMorphedBuildingWrapper_ZergBuildSelf_SetTimer() {
  static CUnit *unit;
  static u16 unitId;
  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV unit, EDI
    MOV unitId, BX
  }

  zergBuildSelf_UpdateBuildTimerAndHp(unit, unitId);

  __asm {
    POPAD
    POP EDI
    POP ESI
    POP EBX
    RETN
  }
}

//-------- cancelZergBuilding --------//

const u32 Hook_IsMorphedBuilding_CancelZergBuildingContinue = 0x0045DA93;
const u32 Func_CancelZergBuildingRemorph = 0x0045D410;
void __declspec(naked) isMorphedBuildingWrapper_CancelZergBuilding() {
  static CUnit *unit;
  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV unit, EBX
  }

  if (!(unit->status & UnitStatus::Completed)
      && hooks::isMorphedBuildingHook(unit->buildQueue[unit->buildQueueSlot]))
  {
    __asm {
      POPAD
      MOV EAX, EBX
      CALL Func_CancelZergBuildingRemorph
      POP EBX
      MOV ESP, EBP
      POP EBP
      RETN 4
    }
  }
  else {
    __asm {
      POPAD
      JMP Hook_IsMorphedBuilding_CancelZergBuildingContinue
    }
  }
}

//-------- AI_GetWaitBuildUnitCount --------//

//Inject @ 0x00433286
const u32 Hook_AI_GetWaitBuildUnitCount_Return = 0x004333D3;
void __declspec(naked) getMorphBuildingTypeCountWrapper_AI_GetWaitBuildUnitCount() {
  static CUnit *unit;
  static u16 unitId;
  static Bool32 ignoreIncomplete;
  static u32 unitCount;

  __asm {
    PUSHAD
    MOV ignoreIncomplete, EDX
    MOV unitId, DI
    MOV unit, ESI
  }

  unitCount = hooks::getMorphBuildingTypeCountHook(unit, unitId, ignoreIncomplete != 0);

  __asm {
    POPAD
    MOV EAX, unitCount
    JMP Hook_AI_GetWaitBuildUnitCount_Return
  }
}

//-------- AI_GetUnitCount --------//

//Inject @ 0x004334D9
const u32 Hook_AI_GetUnitCount_Return = 0x00433588;
void __declspec(naked) getMorphBuildingTypeCountWrapper_AI_GetUnitCount() {
  static CUnit *unit;
  static u16 unitId;
  static u32 unitCount;

  __asm {
    PUSHAD
    MOV unitId, DI
    MOV unit, ESI
    MOV unitCount, EBX
  }

  unitCount += hooks::getMorphBuildingTypeCountHook(unit, unitId, false);

  __asm {
    POPAD
    MOV EBX, unitCount
    JMP Hook_AI_GetUnitCount_Return
  }
}

//-------- AI_ManageBases --------//

//Inject @ 0x00436439
const u32 Hook_AI_ManageBases_Return = 0x004364F7;
void __declspec(naked) getMorphBuildingTypeCountWrapper_AI_ManageBases() {
  static CUnit *unit;
  static u16 unitId;
  static u32 unitCount;

  __asm {
    PUSHAD
    MOV EAX, [EBP-16]
    MOV unitId, AX
    MOV unit, ESI
    MOV unitCount, EBX
  }

  unitCount += hooks::getMorphBuildingTypeCountHook(unit, unitId, false);

  __asm {
    POPAD
    MOV EBX, unitCount
    JMP Hook_AI_ManageBases_Return
  }
}

} //unnamed namespace

extern const u32 Func_IsRemorphingBuilding;

namespace hooks {

void injectBuildingMorphHooks() {
  jmpPatch(isRemorphingBuildingWrapper, Func_IsRemorphingBuilding);
  jmpPatch(isMorphedBuildingWrapper_ConsoleProgressBarText, 0x00426AA2);
  jmpPatch(isMorphedBuildingWrapper_AI_MorphBehavior,       0x0043505F);
  jmpPatch(isMorphedBuildingWrapper_ConsoleWireFrameUpdate, 0x00456911);
  jmpPatch(isMorphedBuildingWrapper_ZergBuildSelf_GetType,  0x0045D505);
  callPatch(isMorphedBuildingWrapper_ZergBuildSelf_Complete, 0x0045D65D);
  jmpPatch(isMorphedBuildingWrapper_ZergBuildSelf_SetTimer, 0x0045D56C);
  jmpPatch(isMorphedBuildingWrapper_CancelZergBuilding,     0x0045DA4A);
  
  jmpPatch(getMorphBuildingTypeCountWrapper_AI_GetWaitBuildUnitCount, 0x00433286);
  jmpPatch(getMorphBuildingTypeCountWrapper_AI_GetUnitCount, 0x004334D9);
  jmpPatch(getMorphBuildingTypeCountWrapper_AI_ManageBases, 0x00436439);
}

} //hooks
