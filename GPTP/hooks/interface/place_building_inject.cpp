#include "place_building.h"
#include <hook_tools.h>

namespace {

const u32 Func_473FB0 = 0x00473FB0;
void __declspec(naked) func473FB0_Wrapper() {

// [EBP+08] unit
// [EBP+0C] playerId
// [EBP+10] x
// [EBP+14] y
// [EBP+18] unitId
// [EBP+1C] unk1
// [EBP+20] unk2
// [EBP+24] unk3
// [EBP+28] unk4

	static CUnit* unit;
	static u32 playerId;
	static s32 x,y;
	static u32 unitId;
	static u32 unk1,unk2,unk3,unk4;

	static u32 return_value;

	__asm {

		PUSH EBP
		MOV EBP, ESP
		SUB ESP, 0x10

		MOV EAX, [EBP+0x08]
		MOV unit, EAX
		MOV EAX, [EBP+0x0C]
		MOV playerId, EAX
		MOV EAX, [EBP+0x10]
		MOV x, EAX
		MOV EAX, [EBP+0x14]
		MOV y, EAX
		MOV EAX, [EBP+0x18]
		MOV unitId, EAX
		MOV EAX, [EBP+0x1C]
		MOV unk1, EAX
		MOV EAX, [EBP+0x20]
		MOV unk2, EAX
		MOV EAX, [EBP+0x24]
		MOV unk3, EAX
		MOV EAX, [EBP+0x28]
		MOV unk4, EAX

		PUSHAD

	}

	return_value = hooks::function_00473FB0(unit, playerId, x, y, unitId, unk1, unk2, unk3, unk4);

	__asm {
		POPAD
		MOV EAX, return_value
		MOV ESP, EBP
		POP EBP
		RETN 0x24
	}

} //func473FB0_Wrapper

;

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
	jmpPatch(func473FB0_Wrapper,				Func_473FB0,						1);
	jmpPatch(placebuildingRefineryCheckWrapper,	Func_placebuildingRefineryCheck,	3);
	jmpPatch(doPlacebuildingCheckingWrapper,	Func_doPlacebuildingChecking,		0);
	jmpPatch(placebuildingNormalProcWrapper,	Func_placebuildingNormalProc,		2);
	jmpPatch(pracebuildingProcWrapper,			Func_pracebuildingProc,				0);
	jmpPatch(issuePlacebuildingOrderWrapper,	Func_issuePlacebuildingOrder,		8);
}

} //hooks
