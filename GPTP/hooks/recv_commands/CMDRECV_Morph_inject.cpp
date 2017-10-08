//Injector source file for the CMDRECV Morph hooks module.
#include "CMDRECV_Morph.h"
#include <hook_tools.h>

namespace {

void __declspec(naked) CMDRECV_BuildingMorphWrapper() {

	static u16 wUnitType;

	__asm {
		MOV AX, [EAX+0x01]
		MOV wUnitType, AX
		PUSHAD
	}

	hooks::CMDRECV_BuildingMorph(wUnitType);

	__asm {
		POPAD
		RETN
	}

}

;

void __declspec(naked) CMDRECV_UnitMorphWrapper() {

	static u16 wUnitType;

	__asm {
		PUSH EBP
		MOV EBP, ESP
		MOV EAX, [EBP+0x08]
		MOV AX, [EAX+0x01]
		MOV wUnitType, AX
		PUSHAD
	}

	hooks::CMDRECV_UnitMorph(wUnitType);

	__asm {
		POPAD
		MOV ESP, EBP
		POP EBP
		RETN 4
	}

}

;

}//unnamed namespace

namespace hooks {

	void injectCMDRECV_MorphHooks() {
		jmpPatch(CMDRECV_BuildingMorphWrapper,	0x004C0CD0, 6);
		jmpPatch(CMDRECV_UnitMorphWrapper,		0x004C0E90, 1);
	}

} //hooks