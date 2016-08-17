#include "spider_mine.h"
#include "../hook_tools.h"

namespace {

void __declspec(naked) findBestSpiderMineTargetWrapper() {

	static CUnit* spiderMine;
	static CUnit* target;

	__asm {
		MOV spiderMine, ESI
		PUSHAD
	}

	target = hooks::findBestSpiderMineTargetHook(spiderMine);

	__asm {
		POPAD
		MOV EAX, target
		RETN
	}

}

;

void __declspec(naked) orders_VultureMineWrapper() {

	static CUnit* unit;

	__asm {
		MOV unit, EAX
		PUSHAD
	}

	hooks::orders_VultureMine(unit);

	__asm {
		POPAD
		RETN
	}

}

;

} //unnamed namespace

namespace hooks {

void injectSpiderMineHooks() {
	jmpPatch(findBestSpiderMineTargetWrapper,	0x00441270, 1);
	jmpPatch(orders_VultureMineWrapper,			0x00463DF0, 2);
}

} //hooks
