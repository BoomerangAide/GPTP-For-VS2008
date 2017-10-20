#include "CMDRECV_Cancel.h"
#include <SCBW/api.h>

//Helper functions declaration

namespace {

void CancelUpgrade_Proc(CUnit* unit);			//54280
void refundQueueSlot(CUnit* unit, u16 slot);	//66A70
void function_00466E40(CUnit* unit);			//66E40
void AI_CancelStructure(CUnit* unit);			//68280
void CancelResearch_Proc(CUnit* unit);			//C0070
void CancelAddon_Proc(CUnit* unit);				//E66E0

} //unnamed namespace

namespace hooks {

//hooked to allow non-ghosts units to cancel nukes
void CMDRECV_CancelNuke() {

	CUnit* current_unit;

	*selectionIndexStart = 0;
	current_unit = getActivePlayerNextSelection();

	while(current_unit != NULL) {

		if(	current_unit->id == UnitId::TerranGhost ||
			current_unit->id == UnitId::Hero_SarahKerrigan ||
			current_unit->id == UnitId::Hero_AlexeiStukov ||
			current_unit->id == UnitId::Hero_SamirDuran ||
			current_unit->id == UnitId::Hero_InfestedDuran
		)
		{

			CUnit* nuke = current_unit->connectedUnit;

			if(nuke != NULL && nuke->id == UnitId::TerranNuclearMissile) {
				current_unit->connectedUnit = NULL;
				nuke->connectedUnit = NULL;
			}

		}

		current_unit = getActivePlayerNextSelection();

	}

}

;

//hooked because the defaut code don't allow multiple selection
void CMDRECV_CancelAddon() {

	CUnit* unit;

	*selectionIndexStart = 0;
	unit = getActivePlayerNextSelection();

	if(	unit != NULL &&
		getActivePlayerNextSelection() == NULL &&
		unit->secondaryOrderId == OrderId::BuildAddon &&
		unit->status & UnitStatus::GroundedBuilding
	)
	{

		CUnit* addon = unit->currentBuildUnit;

		if(	addon != NULL &&
			!(addon->status & UnitStatus::Completed) &&
			unit->status & UnitStatus::Completed &&
			unit->playerId == *ACTIVE_NATION_ID
		)
		{
			CancelAddon_Proc(unit);
			scbw::refreshConsole();
		}

	}

}

;

//hooked because the defaut code don't allow multiple selection
void CMDRECV_CancelUpgrade() {

	CUnit* unit;

	*selectionIndexStart = 0;
	unit = getActivePlayerNextSelection();

	if(	unit != NULL &&
		getActivePlayerNextSelection() == NULL &&
		unit->status & UnitStatus::Completed &&
		unit->playerId == *ACTIVE_NATION_ID
	)
	{
		CancelUpgrade_Proc(unit);
		scbw::refreshConsole();
	}

}

;

//hooked because the defaut code don't allow multiple selection
void CMDRECV_CancelResearch() {

	CUnit* unit;

	*selectionIndexStart = 0;
	unit = getActivePlayerNextSelection();

	if(	unit != NULL &&
		getActivePlayerNextSelection() == NULL &&
		units_dat::BaseProperty[unit->id] & UnitProperty::Building &&
		unit->status & UnitStatus::Completed &&
		unit->playerId == *ACTIVE_NATION_ID
	)
	{
		CancelResearch_Proc(unit);
		scbw::refreshConsole();
	}

}

;

//hooked because the defaut code don't allow multiple selection
void CMDRECV_CancelTrain(u16 wUnitID) {

	CUnit* unit;

	*selectionIndexStart = 0;
	unit = getActivePlayerNextSelection();

	if(	unit != NULL &&
		getActivePlayerNextSelection() == NULL &&
		unit->id != UnitId::ZergLarva &&
		unit->id != UnitId::ZergMutalisk &&
		unit->id != UnitId::ZergHydralisk &&
		unit->id != UnitId::ZergHatchery &&
		unit->id != UnitId::ZergLair &&
		unit->id != UnitId::ZergSpire &&
		unit->id != UnitId::ZergCreepColony &&
		unit->status & UnitStatus::Completed &&
		unit->playerId == *ACTIVE_NATION_ID
	)
	{

		if(wUnitID == 0xFE) {
			function_00466E40(unit);
			scbw::refreshConsole();
		}
		else
		if(wUnitID == 0xFF)
			scbw::refreshConsole();
		else {
			refundQueueSlot(unit,wUnitID);
			scbw::refreshConsole();
		}

	}

}

;

void CMDRECV_CancelUnitMorph() {

	CUnit* current_unit;

	*selectionIndexStart = 0;
	current_unit = getActivePlayerNextSelection();

	while(current_unit != NULL) {

		if(current_unit->playerId == *ACTIVE_NATION_ID)
			AI_CancelStructure(current_unit);

		current_unit = getActivePlayerNextSelection();

	}

}

;

//hooked because the defaut code don't allow multiple selection
void CMDRECV_CancelConstruction() {

	CUnit* unit;

	*selectionIndexStart = 0;
	unit = getActivePlayerNextSelection();

	if(	unit != NULL &&
		getActivePlayerNextSelection() == NULL &&
		unit->playerId == *ACTIVE_NATION_ID
	)
		AI_CancelStructure(unit);

}

;

} //namespace hooks

//-------- Helper function definitions. Do NOT modify! --------//

namespace {

const u32 Func_Sub454280 = 0x00454280;
void CancelUpgrade_Proc(CUnit* unit) {

	__asm {
		PUSHAD
		MOV EAX, unit
		CALL Func_Sub454280
		POPAD
	}

}

;

const u32 Func_refundQueueSlot = 0x00466A70;
void refundQueueSlot(CUnit* unit, u16 slot) {

	__asm {
		PUSHAD
		MOV EDI, unit
		MOVZX EAX, slot
		CALL Func_refundQueueSlot
		POPAD
	}

}

;

const u32 Func_Sub466E40 = 0x00466E40;
void function_00466E40(CUnit* unit) {

	__asm {
		PUSHAD
		MOV EAX, unit
		CALL Func_Sub466E40
		POPAD
	}

}

;

const u32 Func_AI_CancelStructure = 0x00468280;
void AI_CancelStructure(CUnit* unit) {

	__asm {
		PUSHAD
		MOV ECX, unit
		CALL Func_AI_CancelStructure
		POPAD
	}

}

;

const u32 Func_Sub4C0070 = 0x004C0070;
void CancelResearch_Proc(CUnit* unit) {

	__asm {
		PUSHAD
		MOV EDX, unit
		CALL Func_Sub4C0070
		POPAD
	}

}

;

const u32 Func_Sub4E66E0 = 0x004E66E0;
void CancelAddon_Proc(CUnit* unit) {

	__asm {
		PUSHAD
		MOV EAX, unit
		CALL Func_Sub4E66E0
		POPAD
	}

}

;

} //unnamed namespace

//End of helper functions