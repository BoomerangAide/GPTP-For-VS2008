#include "weapon_cooldown.h"
#include "../hook_tools.h"

namespace {

//Inject with jmpPatch()
const u32 Hook_GetModifiedWeaponCooldown  = 0x00475DC0;
void __declspec(naked) getModifiedWeaponCooldownWrapper() {

	static CUnit* unit;
	static u8 weaponId;
	static u32 cooldown;

	__asm {
		MOV unit, ESI
		MOV weaponId, AL
		PUSHAD
	}

  cooldown = hooks::getModifiedWeaponCooldownHook(unit, weaponId);

	__asm {
		POPAD
		MOV EAX, cooldown
		RETN
	}
}

} //unnamed namespace

namespace hooks {

void injectWeaponCooldownHook() {
  jmpPatch(getModifiedWeaponCooldownWrapper, Hook_GetModifiedWeaponCooldown, 2);
}

} //hooks
