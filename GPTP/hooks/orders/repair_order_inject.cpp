#include "repair_order.h"
#include <hook_tools.h>

namespace {

	void __declspec(naked) orders_Repair1Wrapper() {

		static CUnit* unit;

		__asm {
			PUSH EBP
			MOV EBP, ESP
			MOV unit, EAX
			PUSHAD
		}

		hooks::orders_Repair1(unit);

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

void injectRepairOrderHook() {
	jmpPatch(orders_Repair1Wrapper,	0x004673D0,	1);
}

} //hooks