//Injector source file for the Attack Orders hook module.
#include "die_order.h"
#include <hook_tools.h>

namespace {

void __declspec(naked) orders_DieWrapper() {

	static CUnit* unit;

	__asm {
		PUSH EBP
		MOV EBP, ESP

		MOV EAX, [EBP+0x08]
		MOV unit, EAX

		PUSHAD
	}

	hooks::orders_Die(unit);

	__asm {
		POPAD
		POP EBP
		RETN 4
	}
		

}

}//unnamed namespace

namespace hooks {

void injectDieOrderHook() {
	jmpPatch(orders_DieWrapper, 0x00479480, 2);
}

} //hooks