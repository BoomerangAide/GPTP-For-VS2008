#pragma once
#include "../SCBW/structures/CUnit.h"

//V241 for VS2008

namespace hooks {

void transferResourceToWorkerHook(CUnit *worker, CUnit *resource);

void injectHarvestResource();

} //hooks
