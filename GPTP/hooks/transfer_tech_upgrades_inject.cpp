//Injector source file for the Transfer Tech & Upgrades hook module.
#include "transfer_tech_upgrades.h"
#include <hook_tools.h>

namespace {

void __declspec(naked) transferUnitUpgradesToPlayerWrapper() {

	static CUnit* sourceUnit;
	static u8 targetPlayerId;
	static u32 researchUpgradeFunc;

	__asm {

		PUSH EBP
		MOV EBP, ESP

		MOV EAX, [EBP+0x08]
		MOV researchUpgradeFunc, EAX	//2 possibilities, see header file with default values

		MOV sourceUnit, EBX

		MOV EAX, [EBP+0x0C]
		MOV targetPlayerId, AL
		
		PUSHAD

	}

	hooks::transferUnitUpgradesToPlayerHook(sourceUnit, targetPlayerId, researchUpgradeFunc);

	__asm {
		POPAD
		MOV ESP, EBP
		POP EBP
		RETN 0x08
	}

}
	
;

void __declspec(naked) transferUnitTechToPlayerWrapper() {

	static CUnit* sourceUnit;
	static u8 targetPlayerId;
	static u32 researchTechFunc;

	__asm {

		PUSH EBP
		MOV EBP, ESP

		MOV EAX, [EBP+0x08]
		MOV researchTechFunc, EAX		//usually researchTech @ 0047B3C0

		MOV sourceUnit, EBX

		MOV EAX, [EBP+0x0C]
		MOV targetPlayerId, AL
		
		PUSHAD

	}

	hooks::transferUnitTechToPlayerHook(sourceUnit, targetPlayerId, researchTechFunc);

	__asm {
		POPAD
		MOV ESP, EBP
		POP EBP
		RETN 0x08
	}

}
	
;

} //Unnamed namespace

namespace hooks {

void injectTransferTechAndUpgradesHooks() {
  jmpPatch(transferUnitUpgradesToPlayerWrapper,	0x004E2B50, 1);
  jmpPatch(transferUnitTechToPlayerWrapper,		0x004E2C00, 1);
}

} //hooks
