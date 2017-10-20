//Injector source file for the CMDRECV Cancel hooks module.
#include "CMDRECV_Cancel.h"
#include <hook_tools.h>

namespace {

void __declspec(naked) CMDRECV_CancelNukeWrapper() {

	__asm PUSHAD

	hooks::CMDRECV_CancelNuke();

	__asm {
		POPAD
		RETN
	}

}

;

void __declspec(naked) CMDRECV_CancelAddonWrapper() {

	__asm PUSHAD

	hooks::CMDRECV_CancelAddon();

	__asm {
		POPAD
		RETN
	}

}

;

void __declspec(naked) CMDRECV_CancelUpgradeWrapper() {

	__asm PUSHAD

	hooks::CMDRECV_CancelUpgrade();

	__asm {
		POPAD
		RETN
	}

}

;

void __declspec(naked) CMDRECV_CancelResearchWrapper() {

	__asm PUSHAD

	hooks::CMDRECV_CancelResearch();

	__asm {
		POPAD
		RETN
	}

}

;

void __declspec(naked) CMDRECV_CancelTrainWrapper() {

	static u16 wUnitID;

	__asm {
		PUSH EBP
		MOV EBP, ESP
		MOV EAX, [EBP+0x08]
		MOV AX, [EAX+0x01]
		MOV wUnitID, AX
		PUSHAD
	}

	hooks::CMDRECV_CancelTrain(wUnitID);

	__asm {
		POPAD
		POP EBP
		RETN 4
	}

}

;

void __declspec(naked) CMDRECV_CancelUnitMorphWrapper() {

	__asm PUSHAD

	hooks::CMDRECV_CancelUnitMorph();

	__asm {
		POPAD
		RETN
	}

}

;

void __declspec(naked) CMDRECV_CancelConstructionWrapper() {

	__asm PUSHAD

	hooks::CMDRECV_CancelConstruction();

	__asm {
		POPAD
		RETN
	}

}

;

}//unnamed namespace

namespace hooks {

	void injectCMDRECV_CancelHooks() {
		jmpPatch(CMDRECV_CancelNukeWrapper,			0x004BFCD0, 4);
		jmpPatch(CMDRECV_CancelAddonWrapper,		0x004BFF30, 3);
		jmpPatch(CMDRECV_CancelUpgradeWrapper,		0x004BFFC0, 3);
		jmpPatch(CMDRECV_CancelResearchWrapper,		0x004C0070, 3);
		jmpPatch(CMDRECV_CancelTrainWrapper,		0x004C0100, 6);
		jmpPatch(CMDRECV_CancelUnitMorphWrapper,	0x004C2EC0, 2);
		jmpPatch(CMDRECV_CancelConstructionWrapper,	0x004C2EF0, 3);
	}

} //hooks