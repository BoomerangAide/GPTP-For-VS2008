//Injector source file for the Hallucination Spell Order hook module.
#include "feedback_spell.h"
#include <hook_tools.h>

namespace {

	void __declspec(naked) orders_FeedbackWrapper() {

		static CUnit* unit;

		__asm {
			PUSH EBP
			MOV EBP, ESP
			MOV EAX, [EBP+0x08]
			MOV unit, EAX
			PUSHAD
		}

		hooks::orders_Feedback(unit);

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

	void injectFeedbackSpellHook() {
		jmpPatch(orders_FeedbackWrapper, 0x004F6D40, 0);
	}

} //hooks