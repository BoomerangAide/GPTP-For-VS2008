//All functions in this file are meant to be hook helpers for psi_field.h.
//Do NOT modify any functions in this file!

//NOT FULLY REVALIDATED BY UNDEADSTAR

#include "psi_field.h"
#include <hook_tools.h>
#include <SCBW/api.h>

//-------- Unit selection hooks --------//

void showAllPsiFields() {

	static const u32 Func_showAllPsiFields = 0x00493640;

	__asm {
		PUSHAD
		CALL Func_showAllPsiFields
		POPAD
	}

}

void hideAllPsiFields() {

	static const u32 Func_hideAllPsiFields = 0x00494100;

	__asm {
		PUSHAD
		CALL Func_hideAllPsiFields
		POPAD
	}

}

//If @p unit is a psi provider, make all psi field graphics visible.
void showAllPsiFieldsOnSelect(CUnit* unit) {

	if (!scbw::isInReplay() && unit->playerId == *LOCAL_NATION_ID) {
		if ((unit->status & UnitStatus::Completed) && hooks::isReadyToMakePsiField(unit)) {
			showAllPsiFields();
		}
	}

}

//If @p unit is a psi provider, make all psi field graphics invisible.
void hideAllPsiFieldsOnUnselect(CUnit* unit) {

	if (!scbw::isInReplay() && unit->playerId == *LOCAL_NATION_ID) {
		if ((unit->status & UnitStatus::Completed) && hooks::isReadyToMakePsiField(unit)) {
			 hideAllPsiFields();
		}
	}

}

//0x004E6224
void __declspec(naked) showAllPsiFieldsOnSelectWrapper() {

	static CUnit* unit;

	__asm {
		MOV unit, EDI
		PUSHAD
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

//0x004E62BE
void __declspec(naked) hideAllPsiFieldsOnUnselectWrapper() {

	static CUnit* unit;

	__asm {
		MOV unit, ESI
		PUSHAD
	}

	hideAllPsiFieldsOnUnselect(unit);

	__asm {
		POPAD
		POP EDI	//used to be in first asm block
		POP ESI
		RETN
	}

}

//-------- Save & load game hooks --------//

//0x004E3935
void __declspec(naked) packUnitData_PsiProvider() {

	static const u32 packUnitData_PsiProvider_Return = 0x004E3961;

	static CUnit* unit;
	static u16 unitId;
	
	__asm {
		MOV unitId, CX
		MOV unit, ESI
		PUSHAD
	}

	if (hooks::canMakePsiField(unitId)) {
		if (unit->building.pylonAura != NULL)
			*((u32*)&unit->building.pylonAura) = (unit->building.pylonAura - spriteTable) / sizeof(CSprite) + 1;
	}

	__asm {
		POPAD
		JMP packUnitData_PsiProvider_Return
	}

}
//0x004E3182
void __declspec(naked) unpackUnitData_PsiProvider() {

	static const u32 unpackUnitData_PsiProvider_Return = 0x004E31A3;

	static CUnit* unit;
	static u16 unitId;

	__asm {
		MOV unitId, CX
		MOV unit, ESI
		PUSHAD
	}

	if (hooks::canMakePsiField(unitId))
		if (unit->building.pylonAura != NULL)
			unit->building.pylonAura = &spriteTable[(int)unit->building.pylonAura];

	__asm {
		POPAD
		JMP unpackUnitData_PsiProvider_Return
	}

}

//-------- Hook injector --------//
namespace hooks {

void injectPsiFieldHooks() {
	jmpPatch(showAllPsiFieldsOnSelectWrapper,	0x004E6224, 0);
	jmpPatch(hideAllPsiFieldsOnUnselectWrapper,	0x004E62BE, 0);
	jmpPatch(packUnitData_PsiProvider,			0x004E3935, 0);
	jmpPatch(unpackUnitData_PsiProvider,		0x004E3182, 0);
}

} //hooks
