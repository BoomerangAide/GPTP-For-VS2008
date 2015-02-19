#pragma once
#include "../SCBW/structures/CUnit.h"

//V241 for VS2008

namespace hooks {

CUnit* findBestSpiderMineTargetHook(const CUnit *mine);
u8 getSpiderMineBurrowTimeHook(const CUnit *spiderMine);

void injectSpiderMineHooks();

} //hooks
