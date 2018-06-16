//Injector source file for the Mind Control Spell Order hook module.
#include "mindcontrol_spell.h"
#include <hook_tools.h>

namespace {

void __declspec(naked) orders_CastMindControlWrapper() {

	static CUnit* unit;

	__asm {
		PUSH EBP
		MOV EBP, ESP
		MOV EAX, [EBP+0x08]
		MOV unit, EAX
		PUSHAD
	}

	hooks::ordersCastMindControl(unit);

	__asm {
		POPAD
		MOV ESP, EBP
		POP EBP
		RETN 4
	}

}

;

}//unnamed namespace

namespace hooks {

	void injectMindControlSpellHook() {
		jmpPatch(orders_CastMindControlWrapper,	0x004F6950, 0);
	}

} //hooks