#include "utils.h"
#include <SCBW/api.h>

//helper functions def

namespace {

void function_0049A7F0(CUnit* unit); //9A7F0		//sub_49A7F0(selectedUnit)

} //unnamed namespace

namespace hooks {

//0047B770
bool unit_IsStandardAndMovable(CUnit* unit) {

	bool return_value;

	if(
		units_dat::BaseProperty[unit->id] & UnitProperty::Building ||
		units_dat::BaseProperty[unit->id] & UnitProperty::NeutralAccessories ||
		unit->status & UnitStatus::DoodadStatesThing ||
		unit->lockdownTimer != 0 ||
		unit->stasisTimer != 0 ||
		unit->maelstromTimer != 0 ||
		(
			unit->id >= UnitId::Special_FloorMissileTrap &&
			unit->id <= UnitId::Special_RightWallFlameTrap
		) ||
		unit->id == UnitId::TerranVultureSpiderMine ||
		unit->id == UnitId::ZergEgg ||
		unit->id == UnitId::Critter_Rhynadon ||
		unit->id == UnitId::Critter_Bengalaas ||
		unit->id == UnitId::Critter_Ragnasaur ||
		unit->id == UnitId::Critter_Kakaru ||
		unit->id == UnitId::Critter_Scantid ||
		unit->id == UnitId::Critter_Ursadon ||
		unit->id == UnitId::Spell_DarkSwarm ||
		unit->id == UnitId::Spell_DisruptionWeb
	)
		return_value = false;
	else
		return_value = true;

	return return_value;

} //bool unit_IsStandardAndMovable(CUnit* unit)

;

//0049A850
CUnit* getActivePlayerFirstSelection() {

	CUnit* unit;

	if(*selectionIndexStart >= 12)
		unit = NULL;
	else {

		s32 playerId = *ACTIVE_PLAYER_ID;
		u8 index = *selectionIndexStart;
		bool bStopLoop = false;

		while(!bStopLoop) {

			unit = playersSelections->unit[playerId][index];

			if(unit == NULL)
				bStopLoop = true;
			else
			if(unit->sprite != NULL) {
				if(unit->mainOrderId != OrderId::Die)
					bStopLoop = true;
				else
				if(unit->mainOrderState != 1)
					bStopLoop = true;
			}

			if(!bStopLoop)
				function_0049A7F0(unit); //remove the unit from playersSelections->unit[playerId][index] among other things

		}

		*selectionIndexStart = *selectionIndexStart + 1;
		
	}

	return unit;

}

;

} //namespace hooks

;

//-------- Helper function definitions. Do NOT modify! --------//

namespace {

const u32 Func_Sub49A7F0 = 0x0049A7F0;
void function_0049A7F0(CUnit* unit) {

	__asm {
		PUSHAD
		MOV EDI, unit
		CALL Func_Sub49A7F0
		POPAD
	}

}

;

} //Unnamed namespace

//End of helper functions