//The injector source file for the Consume hook module.
#include "consume.h"
#include <hook_tools.h>

namespace {

void __declspec(naked) consumeHitWrapper() {
	static CUnit *target, *caster;

	__asm {
		PUSHAD
		MOV caster, ESI
		MOV target, EAX
	}

  hooks::consumeHitHook(target, caster);

	__asm {
	  POPAD
	  RETN
	}
}

} //Unnamed namespace

namespace hooks {

void injectConsumeHooks() {
  callPatch(consumeHitWrapper, 0x0048BB27);
}

} //hooks