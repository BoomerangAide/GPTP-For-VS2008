//Injector source file for the Weapon/Spell Hit hook module.
#include "wpnspellhit.h"
#include <hook_tools.h>

namespace {

	void __declspec(naked) IrradiateHitWrapper() {

		static CUnit* attacker;
		static CUnit* target;
		static u8 attackingPlayerId;

		__asm {

			PUSH EBP
			MOV EBP, ESP

			MOV EAX, [EBP+0x08]
			MOV attacker, EAX

			MOV AL, [EBP+0x0C]
			MOV attackingPlayerId, AL

			MOV target, EDI

			PUSHAD

		}

		hooks::IrradiateHit(attacker,target,attackingPlayerId);

		__asm {
			POPAD
			POP EBP
			RETN 8
		}

	}

	;

	void __declspec(naked) OpticalFlareHitWrapper() {

		static CUnit* target;
		static u32 attackingPlayerId;
		static CBullet* bullet;

		__asm {

			PUSH EBP
			MOV EBP, ESP

			MOV bullet, EBX

			MOV EBX, [EBP+0x08]			//borrowing EBX
			MOV attackingPlayerId, EBX

			MOV target, EAX

			PUSHAD

		}

		hooks::OpticalFlareHit(target,attackingPlayerId,bullet);

		__asm {
			POPAD
			POP EBP
			RETN 4
		}

	}

	;

	void __declspec(naked) RestoreHitWrapper() {

		static CUnit* target;
		static CBullet* bullet;

		__asm {
			MOV bullet, EAX
			MOV target, EBX
			PUSHAD
		}

		hooks::RestoreHit(target,bullet);

		__asm {
			POPAD
			RETN
		}

	}

	;

	void __declspec(naked) LockdownHitWrapper() {

		static CUnit* target;
		static u8 previousLockdownTimer;
		static CBullet* bullet;

		__asm {

			PUSH EBP
			MOV EBP, ESP

			MOV target, EDI

			MOV AL, [EBP+0x08]
			MOV previousLockdownTimer, AL

			MOV bullet, EBX

			PUSHAD

		}

		hooks::LockdownHit(target,previousLockdownTimer,bullet);

		__asm {
			POPAD
			POP EBP
			RETN 4
		}

	}

	;

	void __declspec(naked) MeleeAttackHitWrapper() {

		static CUnit* attacker;

		__asm {
			PUSH EBP
			MOV EBP, ESP
			MOV attacker, EAX
			PUSHAD
		}

		hooks::MeleeAttackHit(attacker);

		__asm {
			POPAD
			MOV ESP, EBP
			POP EBP
			RETN
		}

	}

	;

	void __declspec(naked) WeaponBulletHitWrapper() {

		static CBullet* bullet;
		static CUnit* target;
		static u32 hitFlags;

		__asm {

			PUSH EBP
			MOV EBP, ESP
			
			MOV bullet, EDX
			MOV target, EAX

			MOV EAX, [EBP+0x08]
			MOV hitFlags, EAX

			PUSHAD

		}

		hooks::WeaponBulletHit(bullet,target,hitFlags);

		__asm {
			POPAD
			POP EBP
			RETN 4
		}

	}

	;

	void __declspec(naked) EMPShockwaveHitWrapper() {

		static CUnit* attacker;
		static CBullet* bullet;
		static int x;
		static int y;

		__asm {

			PUSH EBP
			MOV EBP, ESP

			MOV y, EAX
			MOV x, ECX

			MOV EAX, [EBP+0x08]
			MOV attacker, EAX

			MOV bullet, EBX

			PUSHAD

		}

		hooks::EMPShockwaveHit(attacker,x,y,bullet);

		__asm {
			POPAD
			MOV ESP, EBP
			POP EBP
			RETN 4
		}

	}

	;

	void __declspec(naked) CorrosiveAcidHitWrapper() {

		static int x;
		static int y;
		static u32 playerId;
		static CBullet* bullet;

		__asm {

			PUSH EBP
			MOV EBP, ESP

			MOV x, ECX

			MOV y, EAX

			MOV bullet, EBX

			MOV EAX, [EBP+0x08]
			MOV playerId, EAX

			PUSHAD

		}

		hooks::CorrosiveAcidHit(playerId,x,y,bullet);

		__asm {
			POPAD
			MOV ESP, EBP
			POP EBP
			RETN 4
		}

	}

	;

	void __declspec(naked) ConsumeHitWrapper() {

		static CUnit* attacker;
		static CUnit* target;

		__asm {
			MOV target, EAX
			MOV attacker, ESI
			PUSHAD
		}

		hooks::ConsumeHit(attacker,target);

		__asm {
			POPAD
			RETN
		}

	}

	;

	void __declspec(naked) EnsnareHitWrapper() {

		static CUnit* attacker;
		static int x;
		static int y;
		static CBullet* bullet;

		__asm {

			PUSH EBP
			MOV EBP, ESP

			MOV x, ECX
			MOV y, EAX
			
			MOV EAX, [EBP+0x08]
			MOV attacker, EAX

			MOV bullet, EBX

			PUSHAD

		}

		hooks::EnsnareHit(attacker,x,y,bullet);

		__asm {
			POPAD
			MOV ESP, EBP
			POP EBP
			RETN 4
		}

	}

	;

	void __declspec(naked) DarkSwarmHitWrapper() {

		static int x;
		static int y;
		static u32 attackingPlayerId;
		static CBullet* bullet;

		__asm {

			PUSH EBP
			MOV EBP, ESP

			MOV EAX, [EBP+0x08]
			MOV x, EAX

			MOV EAX, [EBP+0x0C]
			MOV y, EAX

			MOV EAX, [EBP+0x10]
			MOV attackingPlayerId, EAX

			MOV bullet, EBX

			PUSHAD

		}

		hooks::DarkSwarmHit(x,y,attackingPlayerId,bullet);

		__asm {
			POPAD
			POP EBP
			RETN 0x0C
		}

	}

	;

	void __declspec(naked) BroodlingHitWrapper() {

		static CUnit* attacker;
		static CUnit* target;
		static CBullet* bullet;

		__asm {

			PUSH EBP
			MOV EBP, ESP

			MOV EAX, [EBP+0x08]
			MOV attacker, EAX

			MOV EAX, [EBP+0x0C]
			MOV target, EAX

			MOV bullet, EBX

			PUSHAD

		}

		hooks::BroodlingHit(attacker,target,bullet);

		__asm {
			POPAD
			MOV ESP, EBP
			POP EBP
			RETN 0x08
		}

	}

	;

	void __declspec(naked) PlagueHitWrapper() {

		static CUnit* attacker;
		static int x;
		static int y;
		static CBullet* bullet;

		__asm {

			PUSH EBP
			MOV EBP, ESP

			MOV x, ECX
			MOV y, EAX

			MOV EAX, [EBP+0x08]
			MOV attacker, EAX

			MOV bullet, EBX

			PUSHAD

		}

		hooks::PlagueHit(attacker,x,y,bullet);

		__asm {
			POPAD
			MOV ESP, EBP
			POP EBP
			RETN 4
		}

	}

	;

	void __declspec(naked) MaelstromHitWrapper() {

		static CUnit* attacker;
		static int x;
		static int y;
		static CBullet* bullet;

		__asm {

			PUSH EBP
			MOV EBP, ESP

			MOV y, EAX

			MOV EAX, [EBP+0x08]
			MOV x, EAX

			MOV EAX, [EBP+0x0C]
			MOV attacker, EAX

			MOV bullet, EBX

			PUSHAD

		}

		hooks::MaelstromHit(attacker,x,y,bullet);

		__asm {
			POPAD
			MOV ESP, EBP
			POP EBP
			RETN 0x08
		}

	}

	;

	void __declspec(naked) MindControlHitWrapper() {

		static CUnit* attacker;
		static CUnit* target;

		__asm {
			PUSH EBP
			MOV EBP, ESP

			MOV target, ESI

			MOV EAX, [EBP+0x08]
			MOV attacker, EAX

			PUSHAD
		}

		hooks::MindControlHit(attacker,target);

		__asm {
			POPAD
			POP EBP
			RETN 4
		}

	}

	;

	void __declspec(naked) StasisFieldHitWrapper() {

		static CUnit* attacker;
		static int x;
		static int y;
		static CBullet* bullet;

		__asm {

			PUSH EBP
			MOV EBP, ESP

			MOV y, EAX
			MOV x, ECX

			MOV EAX, [EBP+0x08]
			MOV attacker, EAX

			MOV bullet, EBX

			PUSHAD

		}

		hooks::StasisFieldHit(attacker,x,y,bullet);

		__asm {
			POPAD
			MOV ESP, EBP
			POP EBP
			RETN 4
		}

	}

	;

	void __declspec(naked) DisruptionWebHitWrapper() {

		static int x;
		static int y;
		static u32 playerId;
		static CBullet* bullet;

		__asm {

			PUSH EBP
			MOV EBP, ESP

			MOV x, ECX

			MOV y, EAX

			MOV bullet, EBX

			MOV EAX, [EBP+0x08]
			MOV playerId, EAX

			PUSHAD

		}

		hooks::DisruptionWebHit(playerId,x,y,bullet);

		__asm {
			POPAD
			POP EBP
			RETN 0x0C
		}

	}

	;

}//unnamed namespace

namespace hooks {

	void injectWpnSpellHitHooks() {
		jmpPatch(IrradiateHitWrapper,		0x00454E00, 4);
		jmpPatch(OpticalFlareHitWrapper,	0x00455170, 1);
		jmpPatch(RestoreHitWrapper,			0x00455230, 6);
		jmpPatch(LockdownHitWrapper,		0x00455380, 4);
		jmpPatch(WeaponBulletHitWrapper,	0x00479AE0, 1);
		jmpPatch(MeleeAttackHitWrapper,		0x00479B40, 0);
		jmpPatch(EMPShockwaveHitWrapper,	0x00492BA0, 1);
		jmpPatch(CorrosiveAcidHitWrapper,	0x004F4770, 1);
		jmpPatch(ConsumeHitWrapper,			0x004F47B0, 0);
		jmpPatch(EnsnareHitWrapper,			0x004F4830, 1);
		jmpPatch(DarkSwarmHitWrapper,		0x004F48A0, 2);
		jmpPatch(BroodlingHitWrapper,		0x004F4940, 1);
		jmpPatch(PlagueHitWrapper,			0x004F4B30, 1);
		jmpPatch(MaelstromHitWrapper,		0x004F6850, 1);
		jmpPatch(MindControlHitWrapper,		0x004F6910, 8);
		jmpPatch(StasisFieldHitWrapper,		0x004F6A80, 1);
		jmpPatch(DisruptionWebHitWrapper,	0x004F6AF0, 2);
	}

} //hooks
