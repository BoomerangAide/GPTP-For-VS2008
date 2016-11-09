#pragma once
#include "../../../SCBW/structures/CUnit.h"

namespace hooks {

void orders_NukeTrack(CUnit* unit);	//00464D10
void orders_NukeGround(CUnit* unit);//00479200

void injectNukeOrdersHooks();

} //hooks