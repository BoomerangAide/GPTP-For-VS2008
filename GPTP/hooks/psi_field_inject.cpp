//All functions in this file are meant to be hook helpers for psi_field.h.
//Do NOT modify any functions in this file!

#include "psi_field.h"
#include <hook_tools.h>
#include <SCBW/scbwdata.h>
#include <SCBW/api.h>

//-------- Unit selection hooks --------//

void showAllPsiFields() {
  const u32 Func_showAllPsiFields = 0x00493640;

  __asm {
    PUSHAD
    CALL Func_showAllPsiFields
    POPAD
  }
}

void hideAllPsiFields() {
  const u32 Func_hideAllPsiFields = 0x00494100;

  __asm {
    PUSHAD
    CALL Func_hideAllPsiFields
    POPAD
  }
}

//If @p unit is a psi provider, make all psi field graphics visible.
void showAllPsiFieldsOnSelect(CUnit *unit) {
  if (!scbw::isInReplay() && unit->playerId == *LOCAL_NATION_ID) {
    if ((unit->status & UnitStatus::Completed) && hooks::isReadyToMakePsiField(unit)) {
       showAllPsiFields();
    }
  }
}

//If @p unit is a psi provider, make all psi field graphics invisible.
void hideAllPsiFieldsOnUnselect(CUnit *unit) {
  if (!scbw::isInReplay() && unit->playerId == *LOCAL_NATION_ID) {
    if ((unit->status & UnitStatus::Completed) && hooks::isReadyToMakePsiField(unit)) {
       hideAllPsiFields();
    }
  }
}

void __declspec(naked) showAllPsiFieldsOnSelectWrapper() {
  static CUnit *unit;
  __asm {
    PUSHAD
    MOV unit, EDI
  }

  showAllPsiFieldsOnSelect(unit);

  __asm {
    POPAD
    POP EDI
    POP ESI
    POP EBX
    MOV ESP, EBP
    POP EBP
    RETN 4
  }
}

void __declspec(naked) hideAllPsiFieldsOnUnselectWrapper() {
  static CUnit *unit;
  __asm {
    POP EDI   ;//Clean up part of the stack
    PUSHAD
    MOV unit, ESI
  }

  hideAllPsiFieldsOnUnselect(unit);

  __asm {
    POPAD
    POP ESI
    RETN
  }
}

//-------- Save & load game hooks --------//

const u32 packUnitData_PsiProvider_Return = 0x004E3961;
void __declspec(naked) packUnitData_PsiProvider() {
  static CUnit *unit; u16 unitId;
  
  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV unitId, CX
    MOV unit, ESI
  }

  if (hooks::canMakePsiField(unitId)) {
    if (unit->building.pylonAura)
      *(u32*)&unit->building.pylonAura = (unit->building.pylonAura - spriteTable) / sizeof(CSprite) + 1;
  }

  __asm {
    POPAD
    JMP packUnitData_PsiProvider_Return
  }
}

const u32 unpackUnitData_PsiProvider_Return = 0x004E31A3;
void __declspec(naked) unpackUnitData_PsiProvider() {
  static CUnit *unit; u16 unitId;

  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV unitId, CX
    MOV unit, ESI
  }

  if (hooks::canMakePsiField(unitId))
    if (unit->building.pylonAura != 0)
      unit->building.pylonAura = &spriteTable[(int)unit->building.pylonAura];

  __asm {
    POPAD
    JMP unpackUnitData_PsiProvider_Return
  }
}

//-------- Hook injector --------//
namespace hooks {

void injectPsiFieldHooks() {
  jmpPatch(showAllPsiFieldsOnSelectWrapper,   0x004E6224);
  jmpPatch(hideAllPsiFieldsOnUnselectWrapper, 0x004E62BE);
  jmpPatch(packUnitData_PsiProvider,          0x004E3935);
  jmpPatch(unpackUnitData_PsiProvider,        0x004E3182);
}

} //hooks
