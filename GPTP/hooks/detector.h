#pragma once
#include "../SCBW/structures/CUnit.h"

struct DetectorCheckParam {
  u32 visionFlags;
  CUnit* target;
};

C_ASSERT(sizeof(DetectorCheckParam) == 8);

namespace hooks {

bool unitCanDetectHook(CUnit* unit);
void getCloakedTargetVisibility(CUnit* detector, DetectorCheckParam* param);

void injectDetectorHooks();

} //hooks
