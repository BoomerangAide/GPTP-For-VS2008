#include "update_status_effects.h"
#include "../hook_tools.h"

namespace {

//note: acid spores management is normally done in
//function @ 004F42C0, jumped in at the end of this
//one, but the hook merge both

//Inject with jmpPatch()
void __declspec(naked) updateStatusEffectsWrapper() {

	static CUnit* unit;

	__asm {
		MOV unit, EAX
		PUSHAD
	}

	hooks::updateStatusEffects(unit);

	__asm {
		POPAD
		RETN
	}
}

} //unnamed namespace

namespace hooks {

void injectUpdateStatusEffects() {
	jmpPatch(updateStatusEffectsWrapper, 0x00492F70, 5);
}

} //hooks
