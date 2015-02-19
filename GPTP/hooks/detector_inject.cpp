#include "detector.h"
#include "../hook_tools.h"

// V241 for VS2008

extern const u32 Func_CanDetect;  //Defined in CUnit.cpp

namespace {

//Inject with jmpPatch()
void __declspec(naked) unitCanDetectWrapper() {
  static CUnit *unit;
  static u32 result;

  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV unit, EAX
  }

  result = hooks::unitCanDetectHook(unit) ? 1 : 0;

  __asm {
    POPAD
    MOV EAX, result
    RETN
  }
}

struct DetectorCheckParam {
  u32 visionFlags;
  CUnit *target;
};

C_ASSERT(sizeof(DetectorCheckParam) == 8);
//static_assert(sizeof(DetectorCheckParam) == 8, "The size of the DetectorCheckParam structure is invalid");

u32 __fastcall getCloakedTargetVisibilityWrapper(CUnit *unit, DetectorCheckParam *p) {
  p->visionFlags |= hooks::getCloakedTargetVisibility(unit, p->target);
  return 0;
}

} //unnamed namespace

namespace hooks {

void injectDetectorHooks() {
  jmpPatch(unitCanDetectWrapper, Func_CanDetect);
  memoryPatch(0x0044118E, &getCloakedTargetVisibilityWrapper);
  memoryPatch(0x004411A6, &getCloakedTargetVisibilityWrapper);
}

} //hooks
