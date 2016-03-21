//Injector source file for the Recall Spell Order hook module.
#include "recall_spell.h"
#include <hook_tools.h>

namespace {

	void __declspec(naked) spells_Recall_ActionOnValidTargetForRecallWrapper() {

		static CUnit* target;
		static CUnit* caster;

		__asm {
			PUSH EBP
			MOV EBP, ESP
			MOV EAX, [EBP+0x08]
			MOV caster, EAX
			MOV target, EBX
			PUSHAD
		}

		hooks::spells_Recall_ActionOnValidTargetForRecall(target,caster);

		__asm {
			POPAD
			MOV ESP, EBP
			POP EBP
			RETN 4
		}

	}

	;

	void __declspec(naked) spells_Recall_ActionOnTargetInRangeWrapper() {

		static CUnit* target;
		static CUnit* caster;

		__asm {
			MOV target, ECX
			MOV caster, EDX
			PUSHAD
		}

		hooks::spells_Recall_ActionOnTargetInRange(target,caster);

		__asm {
			POPAD
			XOR EAX, EAX //EAX is cleared regardless of the result, keeping it for safety
			RETN
		}

	}

	;

	void __declspec(naked) orders_RecallWrapper() {

		static CUnit* unit;

		__asm {
			PUSH EBP
			MOV EBP, ESP
			MOV EAX, [EBP+0x08]
			MOV unit, EAX
			PUSHAD
		}

		hooks::orders_Recall(unit);

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

	void injectRecallSpellHooks() {
		jmpPatch(spells_Recall_ActionOnValidTargetForRecallWrapper,	0x004942D0, 1);
		jmpPatch(spells_Recall_ActionOnTargetInRangeWrapper,		0x00494400, 3);
		jmpPatch(orders_RecallWrapper,								0x00494470,	1);
	}

} //hooks
