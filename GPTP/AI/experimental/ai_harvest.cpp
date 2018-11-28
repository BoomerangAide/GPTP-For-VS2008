#include "ai_harvest.h"
#include <SCBW/api.h>

//Helper functions definitions

namespace {

CUnit* UpdateUnitFinderDistanceMapping(CUnit* worker, u32 findProc, u32 unkDist, u32 x, u32 y); //E86C0		//UpdateUnitFinderDistanceMapping

} //unnamed namespace

namespace AI {

//004432D0, also known as getNextNearestMineralsEx
//Partially tested when used by human-controlled units only
CUnit* harvestNextNearestResourcesEx(CUnit* mineral_field, CUnit* worker, u16 x, u16 y) {

	const u32 Func_findClosestMineralPatchprocEx = 0x00443280;

	//unknown values of CGame struct, probably related to AI behavior
	const u32* const u32_00586F10 = (u32*)0x00586F10;
	const u32* const u32_00586F40 = (u32*)0x00586F40;
	const u32* const u32_00586F70 = (u32*)0x00586F70;

	u32* const		u32_006955E8 = (u32*)0x006955E8;
	Point16* const	u32_0069579C = (Point16*)0x0069579C;

	const CUnit** NEAREST_MINERAL_FIELD_SAVED = (const CUnit**)0x00695608;

	CUnit* return_value;

	if(
		*u32_00586F10 != NULL ||
		*u32_00586F40 != NULL ||
		*u32_00586F70 != NULL
	)
	{

		u32 distance;
		Point16 pos;

		pos.x = x;pos.y = y;

		*NEAREST_MINERAL_FIELD_SAVED = mineral_field;

		if(mineral_field == NULL)
			distance = 512;
		else
			distance = 256;

		*u32_006955E8 = distance;
		*u32_0069579C = pos;

		return_value = 
			UpdateUnitFinderDistanceMapping(
				worker,
				Func_findClosestMineralPatchprocEx,
				distance,
				x,
				y
			);

	}
	else
		return_value = NULL;

	return return_value;

}

;

//004445E0, renamed from sub_4445E0
//untested
CUnit* FindMineralField(u32 unk_resource_area) {

	CUnit* current_unit = *firstVisibleUnit;
	bool bFoundUnit = false;

	while(current_unit != NULL && !bFoundUnit) {

		if(
			current_unit->sprite != NULL &&
			current_unit->mainOrderId != OrderId::Die &&
			current_unit->id >= UnitId::ResourceMineralField &&
			current_unit->id <= UnitId::ResourceMineralFieldType3 &&
			current_unit->building.resource.resourceGroup == unk_resource_area
		)
			bFoundUnit = true;

		if(!bFoundUnit)
			current_unit = current_unit->link.next;

	}

	return current_unit;

}

;

} //hooks



//-------- Helper function definitions. Do NOT modify! --------//

namespace {

const u32 Func_UpdateUnitFinderDistanceMapping = 0x004E86C0;
CUnit* UpdateUnitFinderDistanceMapping(CUnit* worker, u32 findProc, u32 unkDist, u32 x, u32 y) {

	static CUnit* unit;
	static Point16 pos;

	pos.x = x; pos.y = y;

	__asm {
		PUSHAD
		MOV EAX, unkDist
		MOV EBX, pos
		MOV ESI, y
		PUSH worker
		PUSH findProc
		CALL Func_UpdateUnitFinderDistanceMapping
		MOV unit, EAX
		POPAD
	}

	return unit;

}

;

} //Unnamed namespace

//End of helper functions
