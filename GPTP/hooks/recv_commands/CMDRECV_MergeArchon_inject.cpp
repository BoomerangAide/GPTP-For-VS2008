//Injector source file for the CMDRECV Merge Archon hooks module.
#include "CMDRECV_MergeArchon.h"
#include <hook_tools.h>

namespace {

void __declspec(naked) CMDRECV_MergeDarkArchonWrapper() {

	__asm {
		PUSH EBP
		MOV EBP, ESP
		PUSHAD
	}

	hooks::CMDRECV_MergeDarkArchon();

	__asm {
		POPAD
		MOV ESP, EBP
		POP EBP
		RETN
	}

}

;

void __declspec(naked) CMDRECV_MergeArchonWrapper() {

	__asm {
		PUSH EBP
		MOV EBP, ESP
		PUSHAD
	}

	hooks::CMDRECV_MergeArchon();

	__asm {
		POPAD
		MOV ESP, EBP
		POP EBP
		RETN
	}

}

;

}//unnamed namespace

namespace hooks {

	void injectCMDRECV_MergeArchonHooks() {
		jmpPatch(CMDRECV_MergeDarkArchonWrapper,0x004C0CD0, 1);
		jmpPatch(CMDRECV_MergeArchonWrapper,	0x004C0E90, 1);
	}

} //hooks