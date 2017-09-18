//Injector source file for the Train Command Receive hooks module.
#include "train_cmd_receive.h"
#include <hook_tools.h>

namespace {

	void __declspec(naked) CMDRECV_TrainFighterWrapper() {

		__asm PUSHAD

		hooks::CMDRECV_TrainFighter();

		__asm {
			POPAD
			RETN
		}

	}

	;

	void __declspec(naked) CMDRECV_TrainWrapper() {

		static u16 wUnitType;

		__asm {
			MOV AX, [EAX+01]
			MOV wUnitType, AX
			PUSHAD
		}

		hooks::CMDRECV_Train(wUnitType);

		__asm {
			POPAD
			RETN
		}

	}

	;


}//unnamed namespace

namespace hooks {

	void injectTrainCmdRecvHooks() {
		jmpPatch(CMDRECV_TrainFighterWrapper,	0x004C1800, 5);
		jmpPatch(CMDRECV_TrainWrapper,			0x004C1C20, 7);
	}

} //hooks