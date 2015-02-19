#include "weapon_cooldown.h"
#include "../hook_tools.h"

//V241 for VS2008

namespace {

//Inject with jmpPatch()
const u32 Hook_GetModifiedWeaponCooldown  = 0x00475DC0;
void __declspec(naked) getModifiedWeaponCooldownWrapper() {
	static CUnit *unit;
	static u8 weaponId;
	static u32 cooldown;
	__asm {
		PUSHAD
		MOV ebp, esp
		MOV unit, esi
		MOV weaponId, al
	}

  cooldown = hooks::getModifiedWeaponCooldownHook(unit, weaponId);

	__asm {
		MOV eax, cooldown
		MOV [esp + 28], eax
		POPAD
		RETN
	}
}

} //unnamed namespace

namespace hooks {

void injectWeaponCooldownHook() {
  jmpPatch(getModifiedWeaponCooldownWrapper, Hook_GetModifiedWeaponCooldown);
}

} //hooks