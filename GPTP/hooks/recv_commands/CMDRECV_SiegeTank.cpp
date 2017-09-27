#include "CMDRECV_SiegeTank.h"
#include <SCBW/api.h>

//Helper functions declaration

namespace {

void function_004754F0(CUnit* unit,u32 unitId,u32 unk1,u32 unk2,u32 orderId,u32 unk3,u32 unk4,u32 unk5);	//754F0

} //unnamed namespace

namespace hooks {

void CMDRECV_Siege(u8 bCommandType) {

	CUnit* current_selection;

	*selectionIndexStart = 0;
	current_selection = getActivePlayerNextSelection();

	while(current_selection != NULL) {

		if(
			(current_selection->id == UnitId::TerranSiegeTankTankMode ||
			current_selection->id == UnitId::Hero_EdmundDukeTankMode) &&
			current_selection->mainOrderId != OrderId::SiegeMode
		)
		{
			if(current_selection->canUseTech(TechId::TankSiegeMode,*ACTIVE_NATION_ID) == 1) {

				if(bCommandType != 0)
					bCommandType = 1;
				else
					bCommandType = 0;

				function_004754F0(
					current_selection,
					UnitId::None,
					*(u32*)(0x006D5C24),
					*(u32*)(0x006D5C20),
					OrderId::SiegeMode,
					0,
					bCommandType,
					1
				);

			}
		}

		current_selection = getActivePlayerNextSelection();

	}

}

;

void CMDRECV_Unsiege(u8 bCommandType) {

	CUnit* current_selection;

	*selectionIndexStart = 0;
	current_selection = getActivePlayerNextSelection();

	while(current_selection != NULL) {

		if(
			(current_selection->id == UnitId::TerranSiegeTankSiegeMode ||
			current_selection->id == UnitId::Hero_EdmundDukeSiegeMode) &&
			current_selection->mainOrderId != OrderId::TankMode
		)
		{
			if(current_selection->canUseTech(TechId::TankSiegeMode,*ACTIVE_NATION_ID) == 1) {

				if(bCommandType != 0)
					bCommandType = 1;
				else
					bCommandType = 0;

				function_004754F0(
					current_selection,
					UnitId::None,
					*(u32*)(0x006D5C24),
					*(u32*)(0x006D5C20),
					OrderId::TankMode,
					0,
					bCommandType,
					1
				);

			}
		}

		current_selection = getActivePlayerNextSelection();

	}

}

;

} //namespace hooks

//-------- Helper function definitions. Do NOT modify! --------//

namespace {

	//Note: this function was made from what was seen in this case of use,
	//some things are hardcoded because it's hard to tell what is used or
	//not.
	//Basically, used elsewhere, the function would be implemented differently
	const u32 Func_Sub_4754F0 = 0x004754F0;
	void function_004754F0(CUnit* unit,u32 unitId,u32 unk1,u32 unk2,u32 orderId,u32 unk3,u32 unk4,u32 unk5) {

		__asm {
			PUSHAD
			MOV EAX, 0
			MOV EDX, 0
			MOV EBX, unitId
			MOV ESI, unit
			PUSH unk1
			PUSH unk2
			PUSH unk3
			PUSH orderId
			PUSH unk4
			PUSH unk5
			CALL Func_Sub_4754F0
			POPAD
		}

	}

	;

} //unnamed namespace

//End of helper functions
