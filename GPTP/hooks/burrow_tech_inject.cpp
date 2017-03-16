//Injector source file for the Enter Nydus Order hook module.
#include "burrow_tech.h"
#include <hook_tools.h>

namespace {

	void __declspec(naked) CMDRECV_UnburrowWrapper() {

		__asm PUSHAD

		hooks::CMDRECV_Unburrow();

		__asm {
			POPAD
			RETN
		}

	}

	;

	void __declspec(naked) CMDRECV_BurrowWrapper() {

		static u32 unknown;

		__asm {
			PUSH EBP
			MOV EBP, ESP
			MOV EAX, [EBP+0x08]
			MOV unknown, EAX
			PUSHAD
		}

		hooks::CMDRECV_Burrow(unknown);

		__asm {
			POPAD
			POP EBP
			RETN 4
		}

	}

	;

	void __declspec(naked) Unburrow_ProcWrapper() {

		static CUnit* unit;

		__asm {
			PUSH EBP
			MOV EBP, ESP
			MOV unit, EAX
			PUSHAD
		}

		hooks::Unburrow_Proc(unit);

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

	void injectBurrowTechHooks() {
		jmpPatch(CMDRECV_UnburrowWrapper,	0x004E8C20, 3);
		jmpPatch(CMDRECV_BurrowWrapper,		0x004EA180, 6);
		jmpPatch(Unburrow_ProcWrapper,		0x004EA3E0, 1);
	}

} //hooks