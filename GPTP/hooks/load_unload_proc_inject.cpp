#include "load_unload_proc.h"
#include <hook_tools.h>

namespace {

void __declspec(naked) loadUnitProcWrapper() {

	static CUnit* unit;
	static CUnit* unitToLoad;

	__asm {
		PUSH EBP
		MOV EBP, ESP
		MOV unit, EAX
		MOV unitToLoad, ECX
		PUSHAD
	}

	hooks::loadUnitProc(unit,unitToLoad);

	__asm {
		POPAD
		MOV ESP, EBP
		POP EBP
		RETN
	}

}

;

void __declspec(naked) unloadUnitProcWrapper() {

	static CUnit* unit;
	static u32 return_value;

	__asm {
		PUSH EBP
		MOV EBP, ESP
		MOV unit, EAX
		PUSHAD
	}

	return_value = hooks::unloadUnitProc(unit);

	__asm {
		POPAD
		MOV EAX, return_value
		MOV ESP, EBP
		POP EBP
		RETN
	}

}

;

} //unnamed namespace

namespace hooks {

void injectLoadUnloadProcHooks() {
	jmpPatch(loadUnitProcWrapper,	0x004E78E0,	0);
	jmpPatch(unloadUnitProcWrapper,	0x004E7F70,	1);
}

} //hooks