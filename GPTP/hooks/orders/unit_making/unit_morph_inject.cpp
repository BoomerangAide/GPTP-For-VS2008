#include "unit_morph.h"
#include <hook_tools.h>

namespace {

void __declspec(naked) orders_ZergBirthWrapper() {

	static CUnit* unit;

	__asm {
		PUSH EBP
		MOV EBP, ESP
		MOV unit, EAX
		PUSHAD
	}

	hooks::orders_ZergBirth(unit);

	__asm {
		POPAD
		MOV ESP, EBP
		POP EBP
		RETN
	}

}

;

void __declspec(naked) orders_Morph1Wrapper() {

	static CUnit* unit;

	__asm {
		PUSH EBP
		MOV EBP, ESP
		MOV unit, EAX
		PUSHAD
	}

	hooks::orders_Morph1(unit);

	__asm {
		POPAD
		MOV ESP, EBP
		POP EBP
		RETN
	}

}

;

}; //unnamed namespace

namespace hooks {

	void injectUnitMorphHooks() {
		jmpPatch(orders_ZergBirthWrapper,	0x0045DD60, 1);
		jmpPatch(orders_Morph1Wrapper,		0x0045DEA0, 0);
	}

}; //hooks