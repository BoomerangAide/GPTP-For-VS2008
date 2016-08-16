#include "armor_bonus.h"
#include <hook_tools.h>

extern const u32 Func_GetArmorBonus;	//Defined in CUnit.cpp

namespace {

//Inject with jmpPatch()
void __declspec(naked) getArmorBonusWrapper() {

	static CUnit* unit;
	static u8 armor;

	__asm {
		MOV unit, EAX
		PUSHAD
	}

	armor = hooks::getArmorBonusHook(unit);

	__asm {
		POPAD
		MOVZX EAX, armor
		RETN
	}
}

} //unnamed namespace

namespace hooks {

void injectArmorBonusHook() {
	jmpPatch(getArmorBonusWrapper, Func_GetArmorBonus, 1);
}

} //hooks
