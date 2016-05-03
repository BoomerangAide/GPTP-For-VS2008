//Injector source file for the Cast Order hook module.
#include "cast_order.h"
#include <hook_tools.h>

namespace {

void __declspec(naked) orders_SpellWrapper() {

	static CUnit* unit;

	__asm {
		PUSH EBP
		MOV EBP, ESP
		MOV unit, EAX
		PUSHAD
	}

	hooks::orders_Spell(unit);

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

	void injectCastOrderHooks() {
		jmpPatch(orders_SpellWrapper, 0x00492850, 1);
	}

} //hooks
