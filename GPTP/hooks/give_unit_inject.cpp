//Injector source file for the Give Unit hook module.
#include "give_unit.h"
#include <hook_tools.h>

namespace {

	void __declspec(naked) GiveUnitWrapper() {

		static CUnit* unit;
		static u32 playerId;
		static u32 unkScore;

		__asm {
			PUSH EBP
			MOV EBP, ESP

			MOV EAX, [EBP+0x08]
			MOV playerId, EAX

			MOV EAX, [EBP+0x0C]
			MOV unkScore, EAX

			MOV unit, ECX

			PUSHAD
		}

		hooks::GiveUnit(unit,playerId,unkScore);

		__asm {
			POPAD
			MOV ESP, EBP
			POP EBP
			RETN 0x08
		}

	}

}//unnamed namespace

namespace hooks {

	void injectGiveUnitHook() {
		jmpPatch(GiveUnitWrapper,0x0049EFA0, 1);
	}

} //hooks