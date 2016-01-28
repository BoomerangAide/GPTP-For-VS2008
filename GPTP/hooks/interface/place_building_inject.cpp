#include "place_building.h"
#include <hook_tools.h>

namespace {

const u32 Func_placebuildingRefineryCheck = 0x0048E1E0;
void __declspec(naked) placebuildingRefineryCheckWrapper() {

	static CUnit* unit;

	__asm {
		MOV unit, EAX
		PUSHAD
	}

	hooks::placebuildingRefineryCheck(unit);

	__asm {
		POPAD
		RETN
	}

} //placebuildingRefineryCheckWrapper

;

const u32 Func_doPlacebuildingChecking = 0x0048E210;
void __declspec(naked) doPlacebuildingCheckingWrapper() {

	static CUnit* unit;

	__asm {
		PUSH EBP
		MOV EBP, ESP
		MOV EAX, [EBP+0x08]
		MOV unit, EAX
		PUSHAD
	}

	hooks::doPlacebuildingChecking(unit);

	__asm {
		POPAD
		MOV ESP, EBP
		POP EBP
		RETN 0x0004
	}

} //doPlacebuildingCheckingWrapper

;

const u32 Func_placebuildingNormalProc = 0x0048E490;
void __declspec(naked) placebuildingNormalProcWrapper() {

	__asm PUSHAD

	hooks::placebuildingNormalProc();

	__asm {
		POPAD
		RETN
	}

}

;

const u32 Func_pracebuildingProc = 0x0048E6E0;
void __declspec(naked) pracebuildingProcWrapper() {

	__asm PUSHAD

	hooks::pracebuildingProc();

	__asm {
		POPAD
		RETN
	}

}

;

const u32 Func_issuePlacebuildingOrder = 0x0048E730;
void __declspec(naked) issuePlacebuildingOrderWrapper() {

	static u8 buildOrderId;
	static u32 unitToBuildId;

	__asm {
		PUSH EBP
		MOV EBP, ESP
		MOV AL, [EBP+0x08]
		MOV buildOrderId, AL
		MOV unitToBuildId, ESI
		PUSHAD
	}

	hooks::issuePlacebuildingOrder(buildOrderId,unitToBuildId);

	__asm {
		POPAD
		POP EBP
		RETN 0x0004
	}

}

;

} //unnamed namespace

namespace hooks {

void injectPlaceBuildingHooks() {
	jmpPatch(placebuildingRefineryCheckWrapper,	Func_placebuildingRefineryCheck,	3);
	jmpPatch(doPlacebuildingCheckingWrapper,	Func_doPlacebuildingChecking,		0);
	jmpPatch(placebuildingNormalProcWrapper,	Func_placebuildingNormalProc,		2);
	jmpPatch(pracebuildingProcWrapper,			Func_pracebuildingProc,				0);
	jmpPatch(issuePlacebuildingOrderWrapper,	Func_issuePlacebuildingOrder,		8);
}

} //hooks
