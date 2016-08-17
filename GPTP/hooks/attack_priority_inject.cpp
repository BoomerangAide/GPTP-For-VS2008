#include "attack_priority.h"
#include <hook_tools.h>

namespace {

const u32 Hook_GetAttackPriority = 0x00442160;
//Inject with jmpPatch()
void __declspec(naked) getAttackPriorityWrapper() {

	static CUnit* target, *attacker;
	static u32 result;

	__asm {
		MOV target, EDI
		MOV attacker, EBX
		PUSHAD
	}

	result = hooks::getAttackPriorityHook(target, attacker);

	__asm {
		POPAD
		MOV EAX, result
		RETN
	}

}

const u32 Hook_FindBestAttackTarget = 0x00443080;
//Inject with jmpPatch()
void __declspec(naked) findBestAttackTargetWrapper() {

	static CUnit* unit;
	static CUnit* target;

	__asm {
		PUSH EBP
		MOV EBP, ESP
		MOV unit, EAX
		PUSHAD
	}

	target = hooks::findBestAttackTargetHook(unit);

	__asm {
		POPAD
		MOV EAX, target
		MOV ESP, EBP
		POP EBP
		RETN
	}

}

const u32 Hook_FindRandomAttackTarget = 0x00442FC0;
//Inject with jmpPatch()
void __declspec(naked) findRandomAttackTargetWrapper() {

	static CUnit* unit;
	static CUnit* target;

	__asm {
		PUSH EBP
		MOV EBP, ESP
		MOV unit, ESI
		PUSHAD
	}

	target = hooks::findRandomAttackTargetHook(unit);

	__asm {
		POPAD
		MOV EAX, target
		MOV ESP, EBP
		POP EBP
		RETN
	}
}

} //unnamed namespace

namespace hooks {

void injectAttackPriorityHooks() {
	jmpPatch(getAttackPriorityWrapper,		Hook_GetAttackPriority,			3);
	jmpPatch(findBestAttackTargetWrapper,	Hook_FindBestAttackTarget,		1);
	jmpPatch(findRandomAttackTargetWrapper,	Hook_FindRandomAttackTarget,	1);
}

} //hooks
