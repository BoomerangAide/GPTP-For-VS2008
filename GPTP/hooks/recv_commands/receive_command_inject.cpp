//Injector source file for the Receive Command hook module.
#include "receive_command.h"
#include <hook_tools.h>

namespace {

	void __declspec(naked) receive_commandWrapper() {

		static int x;
		static int y;
		static CUnit* unitParam;
		static u32 wUnitType;
		static u32 bActionOrder;
		static u32 bCommandType;

		__asm {

			PUSH EBP
			MOV EBP, ESP

			MOV EAX, [EBP+0x08]
			MOV x, EAX

			MOV EAX, [EBP+0x0C]
			MOV y, EAX

			MOV EAX, [EBP+0x10]
			MOV unitParam, EAX

			MOV EAX, [EBP+0x14]
			MOV wUnitType, EAX

			MOV EAX, [EBP+0x18]
			MOV bActionOrder, EAX

			MOV EAX, [EBP+0x1C]
			MOV bCommandType, EAX

			PUSHAD

		}

		hooks::receive_command(x,y,unitParam,wUnitType,bActionOrder,bCommandType);

		__asm {
			POPAD
			MOV ESP, EBP
			POP EBP
			RETN 0x18
		}

	}

	;

}//unnamed namespace

namespace hooks {

	void injectRecvCmdHook() {
		jmpPatch(receive_commandWrapper,	0x0049AB00, 1);
	}

} //hooks