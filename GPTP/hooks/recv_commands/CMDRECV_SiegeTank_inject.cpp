//Injector source file for the CMDRECV Siege Tank hooks module.
#include "CMDRECV_SiegeTank.h"
#include <hook_tools.h>

namespace {

void __declspec(naked) CMDRECV_SiegeWrapper() {

	static u8 bCommandType;

	__asm {
		PUSH EBP
		MOV EBP, ESP
		MOV EAX, [EBP+0x08]
		MOV AL, [EAX+1]
		MOV bCommandType, AL
		PUSHAD
	}

	hooks::CMDRECV_Siege(bCommandType);

	__asm {
		POPAD
		POP EBP
		RETN 4
	}

}

;

void __declspec(naked) CMDRECV_UnsiegeWrapper() {

	static u8 bCommandType;

	__asm {
		PUSH EBP
		MOV EBP, ESP
		MOV EAX, [EBP+0x08]
		MOV AL, [EAX+1]
		MOV bCommandType, AL
		PUSHAD
	}

	hooks::CMDRECV_Unsiege(bCommandType);

	__asm {
		POPAD
		POP EBP
		RETN 4
	}

}

}//unnamed namespace

namespace hooks {

	void injectCMDRECV_SiegeTankHooks() {
		jmpPatch(CMDRECV_SiegeWrapper,	0x004C1E80, 6);
		jmpPatch(CMDRECV_UnsiegeWrapper,0x004C1F10, 6);
	}

} //hooks