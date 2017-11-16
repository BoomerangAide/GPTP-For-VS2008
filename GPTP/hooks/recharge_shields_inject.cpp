#include "recharge_shields.h"
#include "../hook_tools.h"

namespace {

void __declspec(naked) unitCanRechargeShieldsWrapper() {

	static CUnit* target;
	static CUnit* battery;
	static Bool32 result;

	__asm {
		MOV battery, EDI
		MOV target, EAX
		PUSHAD
	}

	result = hooks::unitCanRechargeShieldsHook(target, battery);

	__asm {
		POPAD
		MOV EAX, result
		RETN
	}

}

//Inject with callPatch
void __declspec(naked) orderRechargeShieldsWrapper() {

	static CUnit* unit;

	__asm {
		MOV unit, EDI
		PUSHAD
	}

	hooks::orderRechargeShieldsHook(unit);

	__asm {
		POPAD
		RETN
	}

}

} //unnamed namespace

namespace hooks {

void injectRechargeShieldsHooks() {
	jmpPatch(unitCanRechargeShieldsWrapper,	0x00493520, 1);
	jmpPatch(orderRechargeShieldsWrapper,	0x00493DD0, 1);
}

} //hooks
