#include "unit_speed.h"
#include "../hook_tools.h"

namespace {

//Inject with jmpPatch()
void __declspec(naked) getModifiedUnitSpeedWrapper() {
	static CUnit *unit;
	static u32 speed;
	__asm {
		PUSHAD
		MOV ebp, esp
		MOV unit, edx
		MOV speed, eax
	}

  speed = hooks::getModifiedUnitSpeedHook(unit, speed);

	__asm {
		POPAD
    MOV EAX, speed
		RETN
	}
}

//Inject with jmpPatch()
void __declspec(naked) getModifiedUnitAccelerationWrapper() {
	static CUnit *unit;
	static u32 acceleration;
	__asm {
		PUSHAD
		MOV ebp, esp
		MOV unit, ecx
	}

  acceleration = hooks::getModifiedUnitAccelerationHook(unit);

	__asm {
		POPAD
    MOV EAX, acceleration
		RETN
	}
}

//Inject with jmpPatch()
void __declspec(naked) getModifiedUnitTurnSpeedWrapper() {
	static CUnit *unit;
	static u32 turnSpeed;
	__asm {
		PUSHAD
		MOV ebp, esp
		MOV unit, ecx
	}

  turnSpeed = hooks::getModifiedUnitTurnSpeedHook(unit);

	__asm {
		POPAD
    MOV EAX, turnSpeed
		RETN
	}
}

} //unnamed namespace

namespace hooks {

void injectUnitSpeedHooks() {
  jmpPatch(getModifiedUnitSpeedWrapper,         0x0047B5F0);
  jmpPatch(getModifiedUnitAccelerationWrapper,  0x0047B8A0);
  jmpPatch(getModifiedUnitTurnSpeedWrapper,     0x0047B850);
}

} //hooks
