#include "unit_morph.h"
#include <SCBW/api.h>

//helper functions def

namespace {

void fixTargetLocation(Point16* coords, u32 unitId);							//01FA0
bool hasSuppliesForUnit(u32 unitId, u32 playerId, Bool32 canShowErrorMessage);	//2CF70
CUnit* function_0045D910(CUnit* unit);											//5D910
void orderNewUnitToRally(CUnit* unit, CUnit* factory);							//66F50
bool advanceRemainingBuildTime_Sub466940(CUnit* unit);							//66940
void refundAllQueueSlots(CUnit* unit);											//66E80
void actUnitReturnToIdle(CUnit* unit);											//75420
void incrementUnitScoresEx(CUnit* unit, s32 unk1, s32 unk2);					//88D50
void playMorphingCompleteSound(CUnit* unit);									//8F440
void updateUnitStrength(CUnit* unit);											//9FA40
void replaceUnitWithType(CUnit* unit, u16 newUnitId);							//9FED0
void function_004A01F0(CUnit* unit);											//A01F0
void AI_TrainingUnit(CUnit* unit_creator, CUnit* created_unit);					//A2830
void changeUnitButtonSet_Sub4E5D60(CUnit* unit, u16 unitId);					//E5D60
void function_004E65E0(CUnit* unit, Bool32 flag);								//E65E0

} //unnamed namespace

namespace hooks {

void orders_ZergBirth(CUnit* unit) {

	if(unit->orderSignal & 4) {

		bool bTwinEggOrCocoon = true;
		CUnit* unit2;
		Point16 pos;

		unit->orderSignal -= 4;

		if(
			units_dat::BaseProperty[unit->id] & UnitProperty::TwoUnitsIn1Egg ||
			unit->previousUnitType == UnitId::ZergCocoon
		)
			bTwinEggOrCocoon = false;

		unit2 = NULL;

		if(units_dat::BaseProperty[unit->id] & UnitProperty::TwoUnitsIn1Egg) {

			unit2 = function_0045D910(unit);

			if(unit2 != NULL)
				AI_TrainingUnit(unit,unit2);

		}

		if(
			unit->id != UnitId::ZergDrone &&
			unit->id != UnitId::ZergOverlord
		)
			AI_TrainingUnit(unit,unit);

		function_004E65E0(unit,0);

		//update various stuff (set hp, set shield...) not finished on Morph
		function_004A01F0(unit);
		updateUnitStrength(unit);

		pos.x = unit->sprite->position.x;
		pos.y = unit->sprite->position.y;

		if(bTwinEggOrCocoon) {

			if(units_dat::MovementFlags[unit->id] == MovementFlags::HoverUnit)
				pos.y -= 7;
			else
			if(unit->status & UnitStatus::InAir)
				pos.y -= 42;

		}

		fixTargetLocation(&pos,unit->id);

		if(
			pos.x != unit->sprite->position.x ||
			pos.y != unit->sprite->position.y
		)
			scbw::setUnitPosition(unit,pos.x,pos.y);

		if(
			unit->previousUnitType != UnitId::ZergCocoon &&
			unit->previousUnitType != UnitId::ZergLurkerEgg
		)
		{

			orderNewUnitToRally(unit,unit->connectedUnit);

			if(unit2 != NULL)
				orderNewUnitToRally(unit2,unit->connectedUnit);

		}

		actUnitReturnToIdle(unit);

	}

}

;

void orders_Morph1(CUnit* unit) {

	if(unit->mainOrderState == 0) {

		if(
			unit->id == UnitId::ZergLarva ||
			unit->id == UnitId::ZergHydralisk ||
			unit->id == UnitId::ZergMutalisk
		) 
		{

			if(!hasSuppliesForUnit(
						unit->buildQueue[unit->buildQueueSlot],
						unit->playerId,
						1
						)
			)
			{
				refundAllQueueSlots(unit);
				unit->orderComputerCL(units_dat::ReturnToIdleOrder[unit->id]);
			}
			else {

				bool bStopThere = false;
				u16 eggId;

				incrementUnitScoresEx(unit,-1,0);

				//was unit->status = unit->status & ~UnitStatus::Completed
				//in original code
				if(unit->status & UnitStatus::Completed)
					unit->status -= UnitStatus::Completed;

				if(unit->id == UnitId::ZergLarva)
					eggId = UnitId::ZergEgg;
				else
				if(unit->id == UnitId::ZergHydralisk)
					eggId = UnitId::ZergLurkerEgg;
				else
				if(unit->id == UnitId::ZergMutalisk)
					eggId = UnitId::ZergCocoon;
				else
					bStopThere = true;

				if(!bStopThere) {

					replaceUnitWithType(unit,eggId);
					changeUnitButtonSet_Sub4E5D60(unit,unit->id);

					unit->remainingBuildTime = units_dat::TimeCost[unit->buildQueue[unit->buildQueueSlot]];

					unit->mainOrderState = 1;

				}

			}

		}

	}
	else
	if(unit->mainOrderState == 1) {
		if(advanceRemainingBuildTime_Sub466940(unit)) {
			unit->sprite->playIscriptAnim(IscriptAnimation::SpecialState1,true);
			unit->mainOrderState = 2;
		}
	}
	else
	if(unit->mainOrderState == 2) {

		if(unit->orderSignal & 4) {

			unit->orderSignal -= 4;
			replaceUnitWithType(unit,unit->buildQueue[unit->buildQueueSlot]);

			if(
				unit->id == UnitId::ZergDrone ||
				unit->id == UnitId::ZergOverlord
			)
				AI_TrainingUnit(unit,unit);

			playMorphingCompleteSound(unit);

			unit->buildQueue[unit->buildQueueSlot] = UnitId::None;

			if(units_dat::ConstructionGraphic[unit->id] != 0) {

				CImage* current_image;

				function_004E65E0(unit,1);

				current_image = unit->sprite->images.head;

				while(current_image != NULL) {
					current_image->playIscriptAnim(IscriptAnimation::SpecialState1);
					current_image = current_image->link.next;
				}

				unit->orderComputerCL(OrderId::ZergBirth);

			}
			else { //5DF60

				//update various stuff (set hp, set shield...) not finished on Morph
				function_004A01F0(unit);
				updateUnitStrength(unit);

				if(unit->id == UnitId::ZergEgg)
					orderNewUnitToRally(unit,unit->connectedUnit);

			}

		}

	}

}

;

} //namespace hooks

;

//-------- Helper function definitions. Do NOT modify! --------//

namespace {

const u32 Func_fixTargetLocation = 0x00401FA0;
void fixTargetLocation(Point16* coords, u32 unitId) {

	__asm {
		PUSHAD
		MOV EAX, unitId
		MOV EDX, coords
		CALL Func_fixTargetLocation
		POPAD
	}

}

;

const u32 Func_hasSuppliesForUnit = 0x0042CF70;
bool hasSuppliesForUnit(u32 unitId, u32 playerId, Bool32 canShowErrorMessage) {

	static Bool32 bPreResult;

	__asm {
		PUSHAD
		PUSH canShowErrorMessage
		PUSH unitId
		PUSH playerId
		CALL Func_hasSuppliesForUnit
		MOV bPreResult, EAX
		POPAD
	}

	return (bPreResult != 0);

}

;

const u32 Func_Sub45D910 = 0x0045D910;
CUnit* function_0045D910(CUnit* unit) {

	static CUnit* rValue;

	__asm {
		PUSHAD
		PUSH unit
		CALL Func_Sub45D910
		MOV rValue, EAX
		POPAD
	}
	
	return rValue;

}

;

u32 Func_Sub466940 = 0x00466940;
//return true if remainingBuildTime was 0 when called,
//remainingBuildTime change affected by cheating
bool advanceRemainingBuildTime_Sub466940(CUnit* unit) {

	static Bool32 bTimeWasZero;

	__asm {
		PUSHAD
		MOV ECX, unit
		CALL Func_Sub466940
		MOV bTimeWasZero, EAX
		POPAD
	}

	return (bTimeWasZero != 0);

}

;

const u32 Func_RefundAllQueueSlots = 0x00466E80;
void refundAllQueueSlots(CUnit* unit) {

  __asm {
    PUSHAD
	MOV EAX, unit
	CALL Func_RefundAllQueueSlots
    POPAD
  }

}

;

const u32 Func_Sub466F50 = 0x00466F50;
void orderNewUnitToRally(CUnit* unit, CUnit* factory) {

	__asm {
		PUSHAD
		MOV EAX, unit
		MOV ECX, factory
		CALL Func_Sub466F50
		POPAD
	}

}

;

const u32 Func_ActUnitReturnToIdle = 0x00475420;
void actUnitReturnToIdle(CUnit* unit) {

  __asm {
    PUSHAD
    MOV EAX, unit
    CALL Func_ActUnitReturnToIdle
    POPAD
  }

}

;

const u32 Func_incrementUnitScoresEx = 0x00488D50;
//unk1 is ECX, unk2 is pushed value
void incrementUnitScoresEx(CUnit* unit, s32 unk1, s32 unk2) {

	__asm {
		PUSHAD
		MOV EDI, unit
		MOV unk1, ECX
		PUSH unk2
		CALL Func_incrementUnitScoresEx
		POPAD
	}

}

;

const u32 Func_PlayMorphingCompleteSound = 0x0048F440;
void playMorphingCompleteSound(CUnit* unit) {

	__asm {
		PUSHAD
		MOV EAX, unit
		CALL Func_PlayMorphingCompleteSound
		POPAD
	}

}

;

const u32 Func_UpdateUnitStrength = 0x0049FA40;
void updateUnitStrength(CUnit* unit) {

	__asm {
		PUSHAD
		MOV EAX, unit
		CALL Func_UpdateUnitStrength
		POPAD
	}

}

;

const u32 Func_ReplaceUnitWithType = 0x0049FED0;
void replaceUnitWithType(CUnit* unit, u16 newUnitId) {

	u32 newUnitId_ = newUnitId;

  __asm {
    PUSHAD
    PUSH newUnitId_
    MOV EAX, unit
    CALL Func_ReplaceUnitWithType
    POPAD
  }

}

;

const u32 Func_Sub4A01F0 = 0x004A01F0;
void function_004A01F0(CUnit* unit) {

	__asm {
		PUSHAD
		MOV EAX, unit
		CALL Func_Sub4A01F0
		POPAD
	}

}

;

const u32 Func_AI_TrainingUnit = 0x004A2830;
void AI_TrainingUnit(CUnit* unit_creator, CUnit* created_unit) {
	__asm {
		PUSHAD
		MOV EAX, created_unit
		MOV ECX, unit_creator
		CALL Func_AI_TrainingUnit
		POPAD
	}
}

;

const u32 Func_Sub4E5D60 = 0x004E5D60;
void changeUnitButtonSet_Sub4E5D60(CUnit* unit, u16 buttonSetId) {

	__asm {
		PUSHAD
		MOV EAX, unit
		MOV CX, buttonSetId
		CALL Func_Sub4E5D60
		POPAD
	}

}

;

const u32 Func_Sub4E65E0 = 0x004E65E0;
void function_004E65E0(CUnit* unit, Bool32 flag) {

	__asm {
		PUSHAD
		MOV EDI, unit
		PUSH flag
		CALL Func_Sub4E65E0
		POPAD
	}

}

;

} //Unnamed namespace

//End of helper functions
