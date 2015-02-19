#include "spider_mine.h"
#include "../hook_tools.h"

//V241 for VS2008

namespace {

void __declspec(naked) getSpiderMineBurrowTimeWrapper() {
  static CUnit *mine;
  __asm {
    PUSHAD
    MOV mine, EDI
  }

  mine->groundWeaponCooldown = hooks::getSpiderMineBurrowTimeHook(mine);
  mine->mainOrderState = 1;

  __asm {
    POPAD
    RETN
  }
}

void __declspec(naked) findBestSpiderMineTargetWrapper() {
  static CUnit *spiderMine, *target;
  __asm {
    PUSHAD
    MOV spiderMine, ESI
  }

  target = hooks::findBestSpiderMineTargetHook(spiderMine);

  __asm {
    POPAD
    MOV EAX, target
    RETN
  }
}

} //unnamed namespace

namespace hooks {

void injectSpiderMineHooks() {
  callPatch(getSpiderMineBurrowTimeWrapper,   0x00463E08, 3);
  callPatch(findBestSpiderMineTargetWrapper,  0x00463E63);
}

} //hooks