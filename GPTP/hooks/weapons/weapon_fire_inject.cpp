//Injector source file for the Weapon Fire hook module.
#include "weapon_fire.h"
#include <hook_tools.h>

namespace {

void __declspec(naked) fireWeaponWrapper() {

	static CUnit* unit;
	static u8 weaponId;

	__asm {
		PUSH EBP
		MOV EBP, ESP
		MOVZX EAX, [EBP+0x08]
		MOV weaponId, AL
		MOV unit, ESI
		PUSHAD
	}

	hooks::fireWeaponHook(unit, weaponId);

	__asm {
		POPAD
		MOV ESP, EBP
		POP EBP
		RETN 4
	}

}

} //Unnamed namespace

extern const u32 Func_FireUnitWeapon;

namespace hooks {

void injectWeaponFireHooks() {
	jmpPatch(fireWeaponWrapper, Func_FireUnitWeapon, 0);
}

} //hooks
