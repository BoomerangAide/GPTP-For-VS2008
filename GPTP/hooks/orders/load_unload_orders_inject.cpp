#include "load_unload_orders.h"
#include <hook_tools.h>

namespace {

void __declspec(naked) orders_Pickup1Wrapper() {

	static CUnit* unit;

	__asm {
		PUSH EBP
		MOV EBP, ESP
		MOV unit, EAX
		PUSHAD
	}

	hooks::orders_Pickup1(unit);

	__asm {
		POPAD
		MOV ESP, EBP
		POP EBP
		RETN
	}

}

;

void __declspec(naked) orders_Pickup3_0Wrapper() {

	static CUnit* unit;

	__asm {
		MOV unit, EDI
		PUSHAD
	}

	hooks::orders_Pickup3_0(unit);

	__asm {
		POPAD
		RETN
	}

}

;

void __declspec(naked) orders_Pickup2Wrapper() {

	static CUnit* unit;

	__asm {
		MOV unit, EDI
		PUSHAD
	}

	hooks::orders_Pickup2(unit);

	__asm {
		POPAD
		RETN
	}

}

;

void __declspec(naked) orders_MoveUnloadWrapper() {

	static CUnit* unit;

	__asm {
		PUSH EBP
		MOV EBP, ESP
		MOV EAX, [EBP+0x08]
		MOV unit, EAX
		PUSHAD
	}

	hooks::orders_MoveUnload(unit);

	__asm {
		POPAD
		MOV ESP, EBP
		POP EBP
		RETN 4
	}

}

;

void __declspec(naked) orders_Pickup4_0Wrapper() {

	static CUnit* unit;

	__asm {
		PUSH EBP
		MOV EBP, ESP
		MOV unit, EAX
		PUSHAD
	}

	hooks::orders_Pickup4_0(unit);

	__asm {
		POPAD
		MOV ESP, EBP
		POP EBP
		RETN
	}

}

;

void __declspec(naked) orders_EnterTransportWrapper() {

	static CUnit* unit;

	__asm {
		MOV unit, EAX
		PUSHAD
	}

	hooks::orders_EnterTransport(unit);

	__asm {
		POPAD
		RETN
	}

}

;

void __declspec(naked) orders_UnloadWrapper() {

	static CUnit* unit;

	__asm {
		PUSH EBP
		MOV EBP, ESP
		MOV unit, EAX
		PUSHAD
	}

	hooks::orders_Unload(unit);

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

	void injectLoadUnloadOrdersHooks() {
		jmpPatch(orders_Pickup1Wrapper,			0x004E7300, 1);
		jmpPatch(orders_Pickup3_0Wrapper,		0x004E73B0, 1);
		jmpPatch(orders_Pickup2Wrapper,			0x004E75D0, 1);
		jmpPatch(orders_MoveUnloadWrapper,		0x004E7700, 1);
		jmpPatch(orders_Pickup4_0Wrapper,		0x004E7B70, 1);
		jmpPatch(orders_EnterTransportWrapper,	0x004E7CF0, 0);
		jmpPatch(orders_UnloadWrapper,			0x004E80D0, 1);
	}

} //hooks