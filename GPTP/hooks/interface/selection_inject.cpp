#include "selection.h"
#include <hook_tools.h>

namespace {

	const u32 Func_function_0046F3A0 = 0x0046F3A0;
	void __declspec(naked) function_0046FB40_Wrapper() {

		static CUnit* clicked_unit;

		__asm {
			PUSH EBP
			MOV EBP, ESP
			SUB ESP, 0x6C
			MOV EAX, 0x00596A28
			MOVZX EAX, BYTE PTR [EAX]
			PUSH EBX
			PUSH ESI
			MOV ESI, 0x00596A29
			MOVZX ESI, BYTE PTR [ESI]
			PUSH ECX
			PUSH EDX
			MOV [EBP-0x08], EAX
			CALL Func_function_0046F3A0
			MOV [EBP-0x04], EAX
			MOV EBX, EAX
			MOV clicked_unit, EAX
			PUSHAD
		};

		if(clicked_unit != NULL)
			hooks::function_0046FB40(clicked_unit);

		__asm {
			POPAD
			POP ESI
			POP EBX
			MOV ESP, EBP
			POP EBP
			RETN
		}

	}

	;
	
	void __declspec(naked) SortAllUnits_Wrapper() {

		static CUnit* unit;
		static CUnit** unit_list;
		static CUnit** units_in_bounds;
		static u32 result;

		__asm {
			PUSH EBP
			MOV EBP, ESP
			SUB ESP, 0x08
			MOV EAX, [EBP+0x10]
			MOV unit, EAX
			MOV EAX, [EBP+0x0C]
			MOV unit_list, EAX
			MOV EAX, [EBP+0x08]
			MOV units_in_bounds, EAX
			PUSHAD
		}

		result = hooks::SortAllUnits(unit,unit_list,units_in_bounds);

		__asm {
			POPAD
			MOV EAX, result
			MOV ESP, EBP
			POP EBP
			RETN 0x0C
		}

	}

	;

}//unnamed namespace

namespace hooks {

	void injectSelectMod() {
		jmpPatch(function_0046FB40_Wrapper,	0x0046FB40, 27);
		jmpPatch(SortAllUnits_Wrapper,		0x0046F0F0,	 1);
	}

}
