#include "cloak_nearby_units.h"
#include <hook_tools.h>

void __declspec(naked) cloakNearbyUnitsWrapper() {

	static CUnit* unit;

	__asm {
		PUSH EBP
		MOV EBP, ESP
		MOV unit, EDI
		PUSHAD
	}

	hooks::cloakNearbyUnitsHook(unit);

	__asm {
		POPAD
		MOV ESP, EBP
		POP EBP
		RETN
	}

}

namespace hooks {

void injectCloakNearbyUnits() {
	jmpPatch(cloakNearbyUnitsWrapper, 0x00491C20);
}

} //hooks
