#include "nuke_orders.h"
#include <hook_tools.h>

namespace {

void __declspec(naked) orders_NukeTrackWrapper() {

	static CUnit* unit;

	__asm {
		PUSH EBP
		MOV EBP, ESP
		MOV unit, EBX
		PUSHAD
	}

	hooks::orders_NukeTrack(unit);

	__asm {
		POPAD
		MOV ESP, EBP
		POP EBP
		RETN
	}

}

;

void __declspec(naked) orders_NukeGroundWrapper() {

	static CUnit* unit;

	__asm {
		PUSH EBP
		MOV EBP, ESP
		MOV EAX, [EBP+0x08]
		MOV unit, EAX
		PUSHAD
	}

	hooks::orders_NukeGround(unit);

	__asm {
		POPAD
		POP EBP
		RETN 4
	}

}

;

}//unnamed namespace

namespace hooks {

	void injectNukeOrdersHooks() {
		jmpPatch(orders_NukeTrackWrapper,	0x00464D10, 2);
		jmpPatch(orders_NukeGroundWrapper,	0x00479200, 0);
	}

} //hooks