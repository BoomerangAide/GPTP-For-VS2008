//Injector source file for the Hallucination Spell Order hook module.
#include "hallucination_spell.h"
#include <hook_tools.h>

namespace {

	void __declspec(naked) orders_Hallucination1Wrapper() {

		static CUnit* unit;

		__asm {
			PUSH EBP
			MOV EBP, ESP
			MOV unit, EDI
			PUSHAD
		}

		hooks::orders_Hallucination1(unit);

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

	void injectHallucinationSpellHook() {
		jmpPatch(orders_Hallucination1Wrapper, 0x004F6C40, 0);
	}

} //hooks