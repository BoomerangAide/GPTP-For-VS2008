//Injector source file for the Infestation hook module.
#include "infestation.h"
#include <hook_tools.h>

namespace {

//Inject with jmpPatch()
void __declspec(naked) unitCanInfestWrapper() {

  static CUnit* unit;
  static u32 result;

  __asm {
    PUSHAD
	MOV EBP, ESP
    MOV unit, EAX
  }

  result = hooks::unitCanInfest(unit) ? 1 : 0;

  __asm {
    POPAD
    MOV EAX, result
    RETN
  }

}

;

//Inject with jmpPatch()
void __declspec(naked) unitCanBeInfestedWrapper() {

  static CUnit* unit;
  static u32 result;

  __asm {
    PUSHAD
	MOV EBP, ESP
    MOV unit, EDX
  }

  result = hooks::isInfestableUnit(unit) ? 1 : 0;

  __asm {
    POPAD
    MOV EAX, result
    RETN
  }

}

;

//Inject with jmpPatch()
void __declspec(naked) unitMorphIntoInfestedOrder() {

	static CUnit* unitInfested; 

	__asm {
		PUSHAD
		MOV EBP, ESP
		MOV unitInfested, EAX
	}

	hooks::orderMorphIntoInfested(unitInfested);

	__asm {
		POPAD
		RETN
	}

}

;

//Inject with jmpPatch()
void __declspec(naked) unitInfestOrder() {

	static CUnit* unitInfesting;

	__asm {
		PUSHAD
		MOV EBP, ESP
		MOV unitInfesting, EAX
	}

	hooks::orderInfestTarget(unitInfesting);

	__asm {
		POPAD
		RETN
	}

}

;

} //unnamed namespace

namespace hooks {

	void injectInfestationHooks() {
		jmpPatch(unitCanBeInfestedWrapper,		0x00402210);
		jmpPatch(unitCanInfestWrapper,			0x00402750);
		jmpPatch(unitInfestOrder,				0x004EA290);
		jmpPatch(unitMorphIntoInfestedOrder,	0x004EA4C0);
	}

}
