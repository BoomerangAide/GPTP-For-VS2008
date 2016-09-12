#pragma once
#include "../../../SCBW/structures/CUnit.h"

namespace hooks {

	bool isMorphing(CUnit* building);			//0x0045CD00
	void orders_ZergBuildSelf(CUnit* building);	//0x0045D500
	void ZergPlaceBuilding(CUnit* drone);		//0x0045DA40

	void injectBuildingMorphHooks();

} //hooks