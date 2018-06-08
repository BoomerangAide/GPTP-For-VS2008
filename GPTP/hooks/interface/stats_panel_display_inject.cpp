#include "stats_panel_display.h"
#include <hook_tools.h>

namespace {

void __declspec(naked) stats_panel_display_Wrapper() {

	static BinDlg* dialog;

	__asm {
		PUSH EBP
		MOV EBP, ESP
		MOV EAX, [EBP+0x08]
		MOV dialog, EAX
		PUSHAD
	}

	hooks::stats_panel_display(dialog);

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

void injectStatsPanelDisplayHook() {
	//jmpPatch(getLarvaeUnitsFromList_Wrapper,	0x00423190, 1);
	//jmpPatch(BTNSACT_SelectLarva_Wrapper,		0x00423930,	1);
}

} //hooks