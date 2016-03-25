//Injector source file for the Enter Nydus Order hook module.
#include "enter_nydus.h"
#include <hook_tools.h>

namespace {

	void __declspec(naked) canEnterNydusCanalWrapper() {

		static CUnit* unit;
		static CUnit* nydusCanal;
		static Bool32 bReturnValue;

		__asm {
			MOV unit, EAX
			MOV nydusCanal, EDX
			PUSHAD
		}

		if(hooks::canEnterNydusCanal(unit,nydusCanal))
			bReturnValue = 1;
		else
			bReturnValue = 0;

		__asm {
			POPAD
			MOV EAX, bReturnValue
			RETN
		}

	}

	;

	void __declspec(naked) enterNydusCanal_EffectWrapper() {

		static CUnit* unit;
		static CUnit* nydusCanal;

		__asm {
			PUSH EBP
			MOV EBP, ESP
			MOV unit, ECX
			MOV nydusCanal, EAX
			PUSHAD
		}

		hooks::enterNydusCanal_Effect(unit,nydusCanal);

		__asm {
			POPAD
			MOV ESP, EBP
			POP EBP
			RETN
		}

	}

	;

	void __declspec(naked) orders_EnterNydusCanalWrapper() {

		static CUnit* unit;

		__asm {
			MOV unit, EAX
			PUSHAD
		}

		hooks::orders_EnterNydusCanal(unit);

		__asm {
			POPAD
			RETN
		}

	}

	;

}//unnamed namespace

namespace hooks {

	void injectEnterNydusHooks() {
		jmpPatch(canEnterNydusCanalWrapper,		0x004E8C20, 2);
		jmpPatch(enterNydusCanal_EffectWrapper,	0x004EA180, 1);
		jmpPatch(orders_EnterNydusCanalWrapper,	0x004EA3E0, 0);
	}

} //hooks
