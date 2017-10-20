//Injector source file for the CMDRECV Stop hooks module.
#include "CMDRECV_Stop.h"
#include <hook_tools.h>

namespace {

void __declspec(naked) CMDRECV_ReaverStopWrapper() {

	__asm {
		PUSH EBP
		MOV EBP, ESP
		PUSHAD
	}

	hooks::CMDRECV_ReaverStop();

	__asm {
		POPAD
		MOV ESP, EBP
		POP EBP
		RETN
	}

}

;

void __declspec(naked) CMDRECV_CarrierStopWrapper() {

	__asm {
		PUSH EBP
		MOV EBP, ESP
		PUSHAD
	}

	hooks::CMDRECV_CarrierStop();

	__asm {
		POPAD
		MOV ESP, EBP
		POP EBP
		RETN
	}

}

;

void __declspec(naked) CMDRECV_StopWrapper() {

	static u8 bCommandType;

	__asm {
		MOV AL, [EDI+0x01]
		MOV bCommandType, AL
		PUSHAD
	}

	hooks::CMDRECV_Stop(bCommandType);

	__asm {
		POPAD
		RETN
	}

}

;

}//unnamed namespace

namespace hooks {

	void injectCMDRECV_StopHooks() {
		jmpPatch(CMDRECV_ReaverStopWrapper,	0x004C1240, 1);
		jmpPatch(CMDRECV_CarrierStopWrapper,0x004C1430, 1);
		jmpPatch(CMDRECV_StopWrapper,		0x004C2190, 3);
	}

} //hooks