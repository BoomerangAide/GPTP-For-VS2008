#include "unit_train.h"
#include <hook_tools.h>

namespace {

void __declspec(naked) secondaryOrd_TrainFighterWrapper() {

	static CUnit* unit;

	__asm {
		MOV unit, EAX
		PUSHAD
	}

	hooks::secondaryOrd_TrainFighter(unit);

	__asm {
		POPAD
		RETN
	}

}

;

void __declspec(naked) function_00468420Wrapper() {

	static CUnit* unit;

	__asm {
		MOV unit, EAX
		PUSHAD
	}

	hooks::function_00468420(unit);

	__asm {
		POPAD
		RETN
	}

}

}; //unnamed namespace

namespace hooks {

	void injectUnitTrainHooks() {
		jmpPatch(secondaryOrd_TrainFighterWrapper,	0x00466790, 2);
		jmpPatch(function_00468420Wrapper,			0x00468420, 4);
	}

}; //hooks