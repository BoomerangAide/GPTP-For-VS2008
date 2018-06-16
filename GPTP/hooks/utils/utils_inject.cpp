//Injector source file for the Utils hooks module.
#include "utils.h"
#include <hook_tools.h>

namespace {
	
void __declspec(naked) InitializeDialogWrapper() {

	static BinDlg* dialog;
	static void* dlgFunc;

	__asm {
		PUSH EBP
		MOV EBP, ESP
		MOV dialog, ESI
		MOV dlgFunc, EAX
		PUSHAD
	}

	hooks::InitializeDialog(dialog, dlgFunc);

	__asm {
		POPAD
		MOV ESP, EBP
		POP EBP
		RETN
	}

}

;

void __declspec(naked) unit_IsStandardAndMovableWrapper() {

	static CUnit* unit;
	static Bool32 result;

	__asm {
		MOV unit, ECX
		PUSHAD
	}

	if(hooks::unit_IsStandardAndMovable(unit))
		result = 1;
	else
		result = 0;

	__asm {
		POPAD
		MOV EAX, result
		RETN
	}

}
	
;

void __declspec(naked) getActivePlayerFirstSelectionWrapper() {

	static CUnit* unit;

	__asm PUSHAD

	unit = hooks::getActivePlayerFirstSelection();

	__asm {
		POPAD
		MOV EAX, unit
		RETN
	}

}

;

}//unnamed namespace

namespace hooks {

void injectUtilsHooks() {
	jmpPatch(InitializeDialogWrapper,				0x00419D20, 1);
	jmpPatch(unit_IsStandardAndMovableWrapper,		0x0047B770, 2);
	jmpPatch(getActivePlayerFirstSelectionWrapper,	0x0049A850, 2);
}

} //hooks
