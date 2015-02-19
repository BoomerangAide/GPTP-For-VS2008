#include "cloak_nearby_units.h"
#include <hook_tools.h>

//V241 for VS2008

void __declspec(naked) cloakNearbyUnitsWrapper() {
  CUnit *unit;
  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV unit, EDI 
  }

  hooks::cloakNearbyUnitsHook(unit);

  __asm {
    POPAD
    RETN
  }
}

namespace hooks {

void injectCloakNearbyUnits() {
  jmpPatch(cloakNearbyUnitsWrapper, 0x00491C20);
}

} //hooks
