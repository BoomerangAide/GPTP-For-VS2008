//Injector source file for the Create Initial Units hook module.
#include "create_init_units.h"
#include <hook_tools.h>

namespace {

	void __declspec(naked) CreateInitialMeleeBuildingsWrapper() {

		static u32 playerId;
		static u8 raceId;

		__asm {

			PUSH EBP
			MOV EBP, ESP

			MOV raceId, AL

			MOV EAX, [EBP+0x08]
			MOV playerId, EAX

			PUSHAD
		}

		hooks::CreateInitialMeleeBuildings(raceId,playerId);

		__asm {
			POPAD
			MOV ESP, EBP
			POP EBP
			RETN 4
		}

	}

	;

	void __declspec(naked) CreateInitialMeleeUnitsWrapper() {

		__asm {
			PUSH EBP
			MOV EBP, ESP
			PUSHAD
		}

		hooks::CreateInitialMeleeUnits();

		__asm {
			POPAD
			MOV ESP, EBP
			POP EBP
			RETN
		}

	}

	;

	void __declspec(naked) CreateInitialOverlordWrapper() {

		static u8 playerId;

		__asm {

			PUSH EBP
			MOV EBP, ESP

			MOV AL, byte ptr [EBP+0x08]
			MOV playerId, AL

			PUSHAD

		}

		hooks::CreateInitialOverlord(playerId);

		__asm {
			POPAD
			POP EBP
			RETN 4
		}

	}

	;

}//unnamed namespace

namespace hooks {

	void injectCreateInitUnitsHooks() {
		jmpPatch(CreateInitialMeleeBuildingsWrapper,0x0049D7C0, 1);
		jmpPatch(CreateInitialMeleeUnitsWrapper,	0x0049DA40, 1);
		jmpPatch(CreateInitialOverlordWrapper,		0x0049D6C0, 3);
	}

} //hooks