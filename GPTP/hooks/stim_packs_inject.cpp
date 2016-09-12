#include "stim_packs.h"
#include "../hook_tools.h"

namespace {

void __declspec(naked) CMDACT_StimpackWrapper() {

	__asm {
		PUSH EBP
		MOV EBP, ESP
		PUSHAD
	}


	hooks::CMDACT_Stimpack();

	__asm {
		POPAD
		MOV ESP, EBP
		POP EBP
		RETN
	}

}

;

void __declspec(naked) useStimPacksAIWrapper() {

	static CUnit* unit;

	__asm {
		MOV unit, EAX
		PUSHAD
	}

	hooks::useStimPacksAIHook(unit);

	__asm {
		POPAD
		RETN
	}

}

;

void __declspec(naked) CMDRECV_StimPackWrapper() {

	__asm PUSHAD

	hooks::CMDRECV_StimPack();

	__asm {
		POPAD
		RETN
	}

}

;

} //unnamed namespace

namespace hooks {

void injectStimPacksHooks() {
	jmpPatch(CMDACT_StimpackWrapper,	0x004234D0, 4);
	jmpPatch(useStimPacksAIWrapper,		0x004554A0, 5);
	jmpPatch(CMDRECV_StimPackWrapper,	0x004C2F30, 3);
}

} //hooks
