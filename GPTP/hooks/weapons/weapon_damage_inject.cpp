#include "weapon_damage.h"
#include "../../hook_tools.h"

extern const u32 Func_DoWeaponDamage; //Defined in CUnit.cpp

namespace {

//Inject with JmpPatch
void __declspec(naked) weaponDamageWrapper() {

	static CUnit* target;
	static CUnit* attacker;
	static s32 damage;
	static s32 direction;
	static u32 weaponId;
	static u32 damageDivisor;
	static u32 attackingPlayerId;

	__asm {
		PUSH EBP
		MOV EBP, ESP
		MOV damage, EAX
		MOV target, EDI
		MOV EAX, [EBP+0x08]
		MOV weaponId, EAX
		MOV EAX, [EBP+0x0C]
		MOV damageDivisor, EAX
		MOV EAX, [EBP+0x10]
		MOV direction, EAX
		MOV EAX, [EBP+0x14]
		MOV attacker, EAX
		MOV EAX, [EBP+0x18]
		MOV attackingPlayerId, EAX
		PUSHAD
	}

	hooks::weaponDamageHook(damage, target, weaponId, attacker, attackingPlayerId,
							direction, damageDivisor);

	__asm {
		POPAD
		POP EBP
		RETN 0x14
	}
}

} //unnamed namespace

namespace hooks {

void injectWeaponDamageHook() {
	jmpPatch(weaponDamageWrapper, Func_DoWeaponDamage, 1);
}

} //hooks
