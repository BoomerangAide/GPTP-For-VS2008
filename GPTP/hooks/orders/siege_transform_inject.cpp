//Injector source file for the Siege Transformation hook module.
#include "siege_transform.h"
#include <hook_tools.h>

//Inject with jmpPatch()
void __declspec(naked) unitTransformIntoTankModeOrder() {

	static CUnit* unitTransforming; 

	__asm {
		PUSHAD
		MOV EBP, ESP
		MOV unitTransforming, EAX
	}

	hooks::ordersTankMode(unitTransforming);

	__asm {
		POPAD
		RETN
	}

}

//Inject with jmpPatch()
void __declspec(naked) unitTransformIntoSiegeModeOrder() {

	static CUnit* unitTransforming; 

	__asm {
		PUSHAD
		MOV EBP, ESP
		MOV unitTransforming, EDI
	}

	hooks::ordersSiegeMode(unitTransforming);

	__asm {
		POPAD
		RETN
	}

}

namespace hooks {

	void injectSiegeTransformHooks() {
		jmpPatch(unitTransformIntoTankModeOrder,	0x00464AE0, 1);
		jmpPatch(unitTransformIntoSiegeModeOrder,	0x00464BD0, 1);
	}

}
