#pragma once
#include "../SCBW/structures/CUnit.h"

namespace hooks {

CUnit* findBestSpiderMineTargetHook(CUnit* mine);
void orders_VultureMine(CUnit* unit);

void injectSpiderMineHooks();

} //hooks
