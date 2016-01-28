#include "place_building.h"

namespace {

	void updateCurrentButtonset();																/*0x004599A0*/
	bool function_463A10(CUnit* unit, u16 unitId);												/*0x00463A10*/
	void parseUnitsDatReqs();																	/*0x0046E100*/
	u32 function_473EF0(CUnit* unit, u32 playerId, u32 dimensionX, u32 dimensionY, u16 unitId);	/*0x00473EF0*/
	void SetInGameInputProcs();																	/*0x00484CC0*/
	void function_48DAF0(u32 unitToBuildId, Bool32 unknown);									/*0x0048DAF0*/
	void refreshScreen();																		/*0x0048DDC0*/					//refreshScreen
	void placebuildingRefineryProc();															//0x0048E430*/
	void createPylonAura();																		//0x00493640*/
	void function_4D5B60();																		/*0x004D5B60*/
	void function_4F31D0(const char* message);													/*0x004F31D0*/

} //unnamed namespace

namespace hooks {

void placebuildingRefineryCheck(CUnit* unit) {

	u16* const		builtUnitIdRef =	(u16*)	0x0064088A;
	Bool8* const	canBuildCheck =		(Bool8*)0x006D5BE4;

	if(
		*builtUnitIdRef == UnitId::TerranRefinery ||
		*builtUnitIdRef == UnitId::ProtossAssimilator ||
		*builtUnitIdRef == UnitId::ZergExtractor
	)
	{
		if(function_463A10(unit,*builtUnitIdRef))
			*canBuildCheck = 1;
	}

} //void placebuildingRefineryCheck(CUnit* unit)

;

void doPlacebuildingChecking(CUnit* unit) {

	u16* const		u16_00514178 =		(u16*)		0x00514178;	//probably contains unitId entries
	u16* const		u16_0051417A =		(u16*)		0x0051417A;	//probably contains unitId entries
	u16* const		builtUnitIdRef =	(u16*)		0x0064088A;
	Point16* const	point16_00662538 =  (Point16*)	0x00662538;	//may allow to shift the rectangle behind the unit image in build mode?
	u32* const		u32_0066FF60 =		(u32*)		0x0066FF60;	//unknown, also exist in buttonsets.cpp
	Bool8* const	canBuildCheck =		(Bool8*)	0x006D5BE4;

	u16 unitId;
	u32 unitsDatValue;

	*u32_0066FF60 = 0;

	if(units_dat::unitsDat43[unit->id] == 0xFFFF)
		parseUnitsDatReqs();	//update content of units_dat::unitsDat43

	unitsDatValue = units_dat::unitsDat43[unit->id];

	if(
		unitsDatValue == 0 ||
		u16_00514178[unitsDatValue] != 0xFF02
	)
		unitId = UnitId::None;
	else
		unitId = u16_0051417A[unitsDatValue];

	if(unitId == *builtUnitIdRef) {

		s32 dimension_X,dimension_Y;
		u32 result_function;

		dimension_X = units_dat::BuildingDimensions[unit->id].x;
		dimension_Y = units_dat::BuildingDimensions[unit->id].y;

		if(dimension_X < 0)
			dimension_X++;
		if(dimension_Y < 0)
			dimension_Y++;

		dimension_X /= 2;
		dimension_Y /= 2;

		dimension_X = unit->sprite->position.x - dimension_X - point16_00662538[unit->id].x;
		dimension_Y = unit->sprite->position.y - dimension_Y - point16_00662538[unit->id].y;

		if(dimension_X < 0)
			dimension_X += 31;
		if(dimension_Y < 0)
			dimension_Y += 31;

		dimension_X /= 32;
		dimension_Y /= 32;

		result_function = function_473EF0(*activePortraitUnit,(*activePortraitUnit)->playerId,dimension_X,dimension_Y,*builtUnitIdRef);

		if(result_function == 0) {

			if(function_463A10(unit,*builtUnitIdRef))
				*canBuildCheck = 1;

		}

	}

} //void doPlacebuildingChecking(CUnit* unit)

;

void placebuildingNormalProc() {

	CUnit* current_unit = firstPlayerUnit->unit[11];	//was *u32_00628424

	while(current_unit != NULL) {

		if(
			units_dat::BaseProperty[current_unit->id] & UnitProperty::Addon &&
			current_unit->sprite != NULL &&
			current_unit->playerId != 0) 
		{
			doPlacebuildingChecking(current_unit);
		}

		current_unit = current_unit->player_link.next;

	}

} //void placebuildingNormalProc()

;

void pracebuildingProc() {

	u32*	const u32_00640884 =	(u32*)	0x00640884;
	u16*	const builtUnitIdRef =	(u16*)	0x0064088A;
	Bool8*	const canBuildCheck =	(Bool8*)0x006D5BE4;

	if(*u32_00640884 == 0) {

		if(*canBuildCheck != 0) {
			function_4D5B60(); //may do something in a 64*64 area??? (there's a comparison with 64² = 4096)
			*canBuildCheck = 0;
		}

		if(
			*builtUnitIdRef == UnitId::TerranRefinery ||
			*builtUnitIdRef == UnitId::ProtossAssimilator ||
			*builtUnitIdRef == UnitId::ZergExtractor
		)
		{
			placebuildingRefineryProc();
		}
		else
		if(units_dat::GroupFlags[*builtUnitIdRef].isTerran)
			placebuildingNormalProc();

	}

} //void pracebuildingProc()

;

void issuePlacebuildingOrder(u8 buildOrderId, u32 unitToBuildId) {

	u32*		const u32_00640884					= (u32*)		0x00640884;
	u16*		const builtUnitIdRef				= (u16*)		0x0064088A;
	u8*			const u8_0064088C					= (u8*)			0x0064088C;
	u8*			const u8_0064088D					= (u8*)			0x0064088D;
	u32*		const u32_00640958					= (u32*)		0x00640958;
	u16*		const u16_006556FC					= (u16*)		0x006556FC;
	u16*		const BUTTONSET_SPECIAL_BUTTONSETID = (u16*)		0x0068C1C8;
	StringTbl*	const strTbl_006D1220				= (StringTbl*)	0x006D1220;

	*IS_PLACING_BUILDING = 1;
	*BUTTONSET_SPECIAL_BUTTONSETID = UnitId::Buttons_CancelPlaceBuilding;
	updateCurrentButtonset();

	*u32_00640958 = 0;
	*u8_0064088D = buildOrderId;
	function_48DAF0(unitToBuildId,1);	//create image of unit to build

	if(units_dat::BaseProperty[(u16)unitToBuildId] & UnitProperty::Addon) {

		//8E775

		function_48DAF0((*activePortraitUnit)->id,0);	//create image of building attached to addon
		*u32_00640884 = 1;

	}
	else {

		//8e794

		if(
			*builtUnitIdRef == UnitId::TerranRefinery ||
			*builtUnitIdRef == UnitId::ProtossAssimilator ||
			*builtUnitIdRef == UnitId::ZergExtractor
		)
			placebuildingRefineryProc();
		else 
		if(units_dat::GroupFlags[*builtUnitIdRef].isTerran) //8e7B3
			placebuildingNormalProc();	

	}

	//display "Select Location" message
	function_4F31D0(strTbl_006D1220->getString(0x40));

	//store various inputs status in memory so they can be used
	//by functions
	SetInGameInputProcs();

	if(*activePortraitUnit != NULL) {

		if(
			!units_dat::GroupFlags[(*activePortraitUnit)->id].isZerg &&
			units_dat::GroupFlags[(*activePortraitUnit)->id].isProtoss
		)
			createPylonAura();

		if(*activePortraitUnit != NULL) {
			*u8_0064088C = (*activePortraitUnit)->playerId;
			refreshScreen();
			*u16_006556FC = 0;
		}
		else {
			*u8_0064088C = 0xFF;
			refreshScreen();
			*u16_006556FC = 0;
		}

	}
	else {
		*u8_0064088C = 0xFF;
		refreshScreen();
		*u16_006556FC = 0;
	}

} //void issuePlacebuildingOrder(u8 buildOrderId, u32 unitToBuildId)

;

} //namespace hooks 

namespace {

	/**** Definitions of helper functions. Do NOT modify anything below! ****/

	const u32 Func_updateCurrentButtonset = 0x004599A0;
	void updateCurrentButtonset() {
		__asm {
			PUSHAD
			CALL Func_updateCurrentButtonset
			POPAD
		}
	}

	;

	const u32 Func_Sub463A10 = 0x00463A10;
	bool function_463A10(CUnit* unit, u16 unitId) {

		static Bool32 bPreResult;

		__asm {

			PUSHAD

			PUSH unit
			MOV BX, unitId
			CALL Func_Sub463A10

			MOV bPreResult, EAX

			POPAD

		}

		return (bPreResult != 0);

	}

	;

	const u32 Func_parseUnitsDatReqs = 0x0046E100;
	void parseUnitsDatReqs() {

		__asm {
			PUSHAD
			CALL Func_parseUnitsDatReqs
			POPAD
		}

	}

	;

	const u32 Func_Sub473EF0 = 0x00473EF0;
	u32 function_473EF0(CUnit* unit, u32 playerId, u32 dimensionX, u32 dimensionY, u16 unitId) {

		static u32 return_value;

		__asm {

			PUSHAD

			MOV BX, unitId
			PUSH dimensionY
			PUSH playerId
			MOV EDI, dimensionX
			PUSH unit

			CALL Func_Sub473EF0

			MOV return_value, EAX

			POPAD

		}

		return return_value;

	}

	;

	const u32 Func_SetInGameInputProcs = 0x00484CC0;
	void SetInGameInputProcs() {
		__asm {
			PUSHAD
			CALL Func_SetInGameInputProcs
			POPAD
		}
	}

	;

	const u32 Func_Sub48DAF0 = 0x0048DAF0;
	void function_48DAF0(u32 unitToBuildId, Bool32 unknown) {

		__asm {
			PUSHAD
			PUSH unitToBuildId
			PUSH unknown
			CALL Func_Sub48DAF0
			POPAD
		}

	}

	;

	const u32 Func_refreshScreen = 0x0048DDC0;
	void refreshScreen() {
		__asm {
			PUSHAD
			CALL Func_refreshScreen
			POPAD
		}
	}

	;

	const u32 Func_Sub4D5B60 = 0x004D5B60;
	void function_4D5B60() {

		__asm {
			PUSHAD
			CALL Func_Sub4D5B60
			POPAD
		}

	}

	;

	const u32 Func_createPylonAura = 0x00493640;
	void createPylonAura() {
		__asm {
			PUSHAD
			CALL Func_createPylonAura
			POPAD
		}
	}

	;

	const u32 Func_placebuildingRefineryProc = 0x0048E430;
	void placebuildingRefineryProc() {

		__asm {
			PUSHAD
			CALL Func_placebuildingRefineryProc
			POPAD
		}

	}

	;

	const u32 Func_Sub4F31D0 = 0x004F31D0;
	void function_4F31D0(const char* message) {

		__asm {
			PUSHAD
			MOV EDX, message
			CALL Func_Sub4F31D0
			POPAD
		}

	}

} //unnamed namespace
