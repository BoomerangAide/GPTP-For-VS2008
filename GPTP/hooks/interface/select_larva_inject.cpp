#include "select_larva.h"
#include <hook_tools.h>

namespace {

void __declspec(naked) getLarvaeUnitsFromList_Wrapper() {

	static CUnit** unitList;
	static CUnit** outputList;
	static u32 larvaeCount;

	__asm {
		MOV unitList, EDX
		MOV outputList, ESI
		PUSHAD
	}

	larvaeCount = hooks::getLarvaeUnitsFromList(unitList,outputList);

	__asm {
		POPAD
		MOV EAX, larvaeCount
		RETN
	}

}

;

void __declspec(naked) BTNSACT_SelectLarva_Wrapper() {

	__asm {
		PUSH EBP
		MOV EBP, ESP
		PUSHAD
	}

	hooks::BTNSACT_SelectLarva();

	__asm {
		POPAD
		MOV ESP, EBP
		POP EBP
		RETN
	}

}

;

}//unnamed namespace

namespace hooks {

	void injectSelectLarvaHooks() {
		jmpPatch(getLarvaeUnitsFromList_Wrapper,	0x00423190, 1);
		jmpPatch(BTNSACT_SelectLarva_Wrapper,		0x00423930,	1);
	}

} //hooks