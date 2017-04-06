#include "medic_orders.h"
#include <hook_tools.h>

namespace {

	void __declspec(naked) orders_MedicHeal2Wrapper() {

		static CUnit* unit;

		__asm {
			MOV unit, EDI
			PUSHAD
		}

		hooks::orders_MedicHeal2(unit);

		__asm {
			POPAD
			RETN
		}

	}

	;

	void __declspec(naked) orders_HealMoveWrapper() {

		static CUnit* unit;

		__asm {
			PUSH EBP
			MOV EBP, ESP
			MOV EAX, [EBP+0x08]
			MOV unit, EAX
			PUSHAD
		}

		hooks::orders_HealMove(unit);

		__asm {
			POPAD
			MOV ESP, EBP
			POP EBP
			RETN 4
		}

	}

	;

	void __declspec(naked) orders_MedicWrapper() {

		static CUnit* unit;

		__asm {
			PUSH EBP
			MOV EBP, ESP
			MOV unit, EAX
			PUSHAD
		}

		hooks::orders_Medic(unit);

		__asm {
			POPAD
			MOV ESP, EBP
			POP EBP
			RETN
		}

	}

	;

	void __declspec(naked) orders_MedicHeal1Wrapper() {

		static CUnit* unit;

		__asm {
			MOV unit, EAX
			PUSHAD
		}

		hooks::orders_MedicHeal1(unit);

		__asm {
			POPAD
			RETN
		}

	}

	;

}//unnamed namespace

namespace hooks {

void injectMedicOrdersHooks() {
	jmpPatch(orders_MedicHeal2Wrapper,	0x00463740, 1);
	jmpPatch(orders_HealMoveWrapper,	0x004637B0, 1);
	jmpPatch(orders_MedicWrapper,		0x00463900, 1);
	jmpPatch(orders_MedicHeal1Wrapper,	0x00464180, 1);
}

} //hooks