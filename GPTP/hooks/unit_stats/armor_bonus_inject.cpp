#include "armor_bonus.h"
#include <hook_tools.h>

//V241 for VS2008

extern const u32 Func_GetArmorBonus;  //Defined in CUnit.cpp

namespace {

//Inject with jmpPatch()
void __declspec(naked) getArmorBonusWrapper() {
  CUnit *unit;
  u8 armor;
  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV unit, EAX
  }

  armor = hooks::getArmorBonusHook(unit);

  __asm {
    MOVZX EAX, armor
    MOV [ESP + 28], EAX
    POPAD
    RETN
  }
}

} //unnamed namespace

namespace hooks {

void injectArmorBonusHook() {
  jmpPatch(getArmorBonusWrapper, Func_GetArmorBonus);
}

} //hooks
