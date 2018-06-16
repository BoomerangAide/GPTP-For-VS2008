//Injector source file for the Apply Upgrade Flags hook module.
#include "apply_upgrade_flags.h"
#include <hook_tools.h>

namespace {

void __declspec(naked) applyUpgradeFlagsToNewUnitWrapper() {

	static CUnit* unit;

	__asm {
		MOV unit, ESI
		PUSHAD
	}

	hooks::applyUpgradeFlagsToNewUnitHook(unit);

	__asm {
		POPAD
		RETN
	}
}

;

void __declspec(naked) applyUpgradeFlagsToExistingUnitsWrapper() {

	static CUnit* unit;
	static u8 upgradeId;

	__asm {

		PUSH EBP
		MOV EBP, ESP

		MOV upgradeId, AL

		MOV EAX, [EBP+0x08]
		MOV unit, EAX

		PUSHAD

	}

	hooks::applyUpgradeFlagsToExistingUnitsHook(unit, upgradeId);

	__asm {
		POPAD
		MOV ESP, EBP
		POP EBP
		RETN 4
	}
}

} //Unnamed namespace

namespace hooks {

void injectApplyUpgradeFlags() {
	jmpPatch(applyUpgradeFlagsToNewUnitWrapper,			0x00454370, 2);
	jmpPatch(applyUpgradeFlagsToExistingUnitsWrapper,	0x00454540, 2);
}
	
;

} //hooks
