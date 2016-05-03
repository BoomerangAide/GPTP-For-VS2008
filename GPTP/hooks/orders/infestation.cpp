#include "infestation.h"
#include <SCBW/api.h>

//Helper functions definitions

namespace {

void orderReturnToIdle(CUnit* unit);												//0x00463770
void disconnectFromAddOn(CUnit* unit);												//0x00464930
void refundAllQueueSlots(CUnit* unit);												//0x00466E80
void removeOrderFromUnitQueue(CUnit* unit);											//0x004742D0
void actUnitReturnToIdle(CUnit* unit);												//0x00475420
void incrementUnitDeathScores(CUnit* unit, u8 player);								//0x00488AF0
void incrementUnitScores(CUnit* unit, s8 value);									//0x00488BF0, 0x00488D50
void initializeEmptyUnitsLinkedListRef_Sub49E4E0(CUnit* unit, u8 playerId);			//0x0049E4E0
void readUnitsArray_Sub49EFA0(CUnit* unit, u8 playerId);							//0x0049EFA0
void changeUnitButtonSet_Sub_4E5D60(CUnit* unit, u16 unitId);						//0x004E5D60
void hideAndDisableUnit(CUnit* unit);												//0x004E6340
void showAndEnableUnit(CUnit* unit);												//0x004E6490
void setNextWaypoint_Sub4EB290(CUnit* unit);										//0x004EB290
void makeToHoldPosition(CUnit* unit);												//0x004EB5B0

} //unnamed namespace

namespace hooks {

	//replace 0x00402750 canInfest
	bool unitCanInfest(const CUnit* unit) {

		bool returnValue;

		returnValue = (unit->id == UnitId::queen || unit->id == UnitId::matriarch);

		return returnValue;

	}

	;

	//replace 0x00402210 CC_CanBeInfested
	bool isInfestableUnit(const CUnit* unit) {

		u32 unitHpTest;
		u32 unitMaxHp;
		bool returnValue;

		returnValue = (unit->status & UnitStatus::Completed) && (unit->id == UnitId::command_center);

		if (returnValue) {

			unitMaxHp = unit->getMaxHpInGame();
			unitHpTest = unit->getCurrentHpInGame();

			//if HP/maxHP higher or equal than 50%, not damaged enough
			if( ( (100 * unitHpTest) / unitMaxHp ) >= 50 )
				returnValue = false;

		}

		return returnValue;

	}

	;

	//Based on and replace orders_InfestMine1 (0x004EA4C0)
	void orderMorphIntoInfested(CUnit* unitInfested) {

		bool bErrorReturnToIdle;
		bool bStopFunction = false;

		u16 infestedUnitNewId;
		u16 infestationOverlayId;

		CUnit* unitInfesting = unitInfested->orderTarget.unit;

		bErrorReturnToIdle = (unitInfesting == NULL || !isInfestableUnit(unitInfested));

		if(!bErrorReturnToIdle) {

			if(unitInfested->mainOrderState == 0) {

				//init timer
				unitInfested->remainingBuildTime = 3;
				unitInfested->mainOrderState = 2;
				bStopFunction = true;

			}

			if(!bStopFunction) {

				if(unitInfested->remainingBuildTime != 0) {

					//advancing timer
					unitInfested->remainingBuildTime--;
					bStopFunction = true;

				}
				else {

					//will become 0xffff, this is used by internal functions
					unitInfested->remainingBuildTime--;

					//disconnect terran buildings from their add-on
					if(unitInfested->building.addon != NULL)
						disconnectFromAddOn(unitInfested);

					//this is the same as calling 0047B2E0 unitIsFactoryUnit like original code but faster
					if(unitInfested->isFactory())
						unitInfested->rally.unit = unitInfested;

					//original code was *(u16*)(0x006648AC + 2*unitInfested->id);
					infestedUnitNewId = units_dat::InfestedUnitPartial[unitInfested->id - UnitId::TerranCommandCenter];

					//update number of kills/casualties for endgame score
					incrementUnitDeathScores(unitInfested, unitInfesting->playerId);

					//effect unknown, don't seem to affect score screen at endgame
					incrementUnitScores(unitInfested, -1);
					incrementUnitScores(unitInfested, 1);

					//the unit receive the new id (infested id)
					unitInfested->id = infestedUnitNewId;

					//I don't really know, advanced internal mechanics, just have to work with it
					readUnitsArray_Sub49EFA0(unitInfested, unitInfesting->playerId);
					initializeEmptyUnitsLinkedListRef_Sub49E4E0(unitInfested, unitInfesting->playerId);

					//Related to infestation process
					unitInfested->setSecondaryOrder(OrderId::Nothing2);

					//refund what the unit was producing
					refundAllQueueSlots(unitInfested);

					//clear the orders queue of the unit
					while(unitInfested->orderQueueHead != NULL)
						removeOrderFromUnitQueue(unitInfested);

					if((unitInfested->status & UnitStatus::GroundedBuilding)) {

						CImage* current_image = unitInfested->sprite->images.head;

						while(current_image != NULL) {

							//script 0x14 in asm code
							current_image->playIscriptAnim(IscriptAnimation::WorkingToIdle);

							//load next image of the list (or NULL)
							current_image = current_image->link.next;

						}

					}

					//Just use ImageId::InfestedCommandCenterOverlay instead
					//if you're modding this file and you're going for the
					//default infestation overlay for any target.
					infestationOverlayId = units_dat::ConstructionGraphic[UnitId::infested_command_center];

					//asm would compare with hardcoded 999
					if(infestationOverlayId != ImageId::None)
						unitInfested->sprite->createOverlay(infestationOverlayId);

					//Assembly code is using
					//*(u16*)(0x00662350 + unitInfested->id)
					unitInfested->setHp(units_dat::MaxHitPoints[unitInfested->id]);

					//give the proper button set to the unit
					changeUnitButtonSet_Sub_4E5D60(unitInfested, unitInfested->id);

					scbw::refreshConsole();

				} //if(unitInfested->remainingBuildTime == 0)

			} //if(!bStopFunction)

		} //if(!bErrorReturnToIdle)

		if(!bStopFunction)
			orderReturnToIdle(unitInfested);

	}


	;

	//Based on and replace 004EA290 orders_InfestMine4
	void orderInfestTarget(CUnit* unitInfesting) {

		CUnit* unitInfested = unitInfesting->orderTarget.unit;
		bool bBuildTimeReachedZero = false;
		bool bStopFunction = false;
		bool bReturnToIdle = false;

		Point16 actualpos;

		if(unitInfesting->mainOrderState == 3) {

			//infesting in progress, dealing with timer
			
			if(unitInfesting->remainingBuildTime != 0) {
				unitInfesting->remainingBuildTime--;
				bStopFunction = true;
			}
			else
				bBuildTimeReachedZero = true;

		}
		else
		if(unitInfesting->mainOrderState != 0) // if ==0, wait for EA33F to start infestation logic
			bStopFunction = true;

		if(!bStopFunction && bBuildTimeReachedZero) { 

			//EA2CC
			//Infestation timer ended

			//code made based on similar code in api.cpp, seems to work, but this really came out
			//different from the assembly code
			if(scbw::checkUnitCollisionPos(unitInfesting, &unitInfested->sprite->position, &actualpos)) {

				scbw::setUnitPosition(unitInfesting, actualpos.x, actualpos.y);
				makeToHoldPosition(unitInfesting);
				showAndEnableUnit(unitInfesting);

				if(unitInfesting->orderQueueHead != NULL) {
					unitInfesting->orderSimple(units_dat::ReturnToIdleOrder[unitInfesting->id],false);
					bReturnToIdle = true;
				}
				else
					bReturnToIdle = true;

			}
			else
				bStopFunction = true;

		} //if(!bStopFunction && bBuildTimeReachedZero) {

		if(bReturnToIdle)
			actUnitReturnToIdle(unitInfesting);
		else
		if(!bStopFunction) { //EA33F

			//not started the infestation logic yet, doing it here

			if(		unitInfested != NULL && 
					isInfestableUnit(unitInfested) &&
					unitInfested->mainOrderId != OrderId::InfestMine1) {

				hideAndDisableUnit(unitInfesting);								//hide the infesting unit
				unitInfested->orderTo(OrderId::InfestMine1, unitInfesting);		//order the target to be infested, giving it the infesting unit as order target
				unitInfesting->mainOrderState = 3;
				unitInfesting->remainingBuildTime = 60; //timer before reappearing
				bStopFunction = true;

			}

			if(!bStopFunction) { //EA377

				//"move to invalid target" logic...I think

				setNextWaypoint_Sub4EB290(unitInfesting);

				if(	unitInfesting->moveTarget.pt.x != unitInfesting->nextTargetWaypoint.x ||
					unitInfesting->moveTarget.pt.y != unitInfesting->nextTargetWaypoint.y) {

					unitInfesting->nextTargetWaypoint.x = unitInfesting->moveTarget.pt.x;
					unitInfesting->nextTargetWaypoint.y = unitInfesting->moveTarget.pt.y;

				}

				//EA39E

				if(unitInfesting->orderQueueHead != NULL)
					actUnitReturnToIdle(unitInfesting);
				else {

					unitInfesting->order(
						units_dat::ReturnToIdleOrder[unitInfesting->id],
						0, 
						0, 
						NULL, 
						UnitId::None, 
						true);

					actUnitReturnToIdle(unitInfesting);

				}

			}	

		} //if(!bStopFunction && bBuildTimeReachedZero)


	} //void orderInfestTarget(CUnit* unitInfesting)

	;

} //hooks



//-------- Helper function definitions. Do NOT modify! --------//

namespace {

const u32 Func_OrderReturnToIdle = 0x00463770;
void orderReturnToIdle(CUnit* unit) {

  __asm {
    PUSHAD
	MOV ESI, unit
    CALL Func_OrderReturnToIdle
    POPAD
  }

}

;

const u32 Func_Sub_464930 = 0x00464930;
void disconnectFromAddOn(CUnit* unit) {

  __asm {
    PUSHAD
    MOV EAX, unit
    CALL Func_Sub_464930
    POPAD
  }

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

const u32 Func_removeOrderFromUnitQueue = 0x004742D0;
void removeOrderFromUnitQueue(CUnit* unit) {

	static COrder* orderQueueHead = unit->orderQueueHead;

  __asm {
    PUSHAD
	MOV ECX, unit
	MOV EAX, orderQueueHead
	CALL Func_removeOrderFromUnitQueue
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

//Related to path/movement decision
const u32 Func_sub_4EB290 = 0x004EB290;
void setNextWaypoint_Sub4EB290(CUnit* unit) {

  __asm {
    PUSHAD
    MOV EAX, unit
    CALL Func_sub_4EB290
    POPAD
  }
}

;

const u32 Func_IncrementUnitDeathScores = 0x00488AF0;
void incrementUnitDeathScores(CUnit* unit, u8 player) {

  __asm {
    PUSHAD
    MOV EDI, unit
    MOVZX EDX, player
    CALL Func_IncrementUnitDeathScores
    POPAD
  }

}

;

const u32 Func_IncrementUnitScores = 0x00488BF0;
const u32 Func_IncrementUnitScoresEx = 0x00488D50;
void incrementUnitScores(CUnit* unit, s8 value) {

	if(value == -1)

		__asm {

			PUSHAD

			PUSH -0x01
			MOV EAX, unit
			CALL Func_IncrementUnitScores

			TEST byte ptr[EDI+0x000000DC], 0x01		/*test unit->status & UnitStatus::Completed*/
			JE neg_value_skip

			PUSH 0x00
			MOV ECX, 0x0000FFFF
			CALL Func_IncrementUnitScoresEx

			neg_value_skip:

			POPAD

		}

	else
	if (value == 1)

		__asm {

			PUSHAD

			PUSH 0x01
			MOV EAX, unit
			CALL Func_IncrementUnitScores

			TEST byte ptr[EDI+0x000000DC], 0x01		/*test unit->status & UnitStatus::Completed*/
			JE pos_value_skip

			PUSH 0x00
			MOV ECX, 0x00000001
			CALL Func_IncrementUnitScoresEx

			pos_value_skip:

			POPAD

		}

}

;

const u32 Func_Sub_49E4E0 = 0x0049E4E0;
void initializeEmptyUnitsLinkedListRef_Sub49E4E0(CUnit* unit, u8 playerId) {

  __asm {

    PUSHAD

	MOV DL, playerId
	MOV ECX, unit

	CALL Func_Sub_49E4E0

    POPAD

  }

}

;

const u32 Func_Sub_49EFA0 = 0x0049EFA0;
//non-generic version specific to this context
void readUnitsArray_Sub49EFA0(CUnit* unit, u8 playerId) {

  __asm {

    PUSHAD

	XOR EAX, EAX
	MOV AL, playerId

	PUSH 0x01

	MOV ECX, unit
	PUSH EAX

	CALL Func_Sub_49EFA0

    POPAD

  }

}

;

const u32 Func_Sub_4E5D60 = 0x004E5D60;
void changeUnitButtonSet_Sub_4E5D60(CUnit* unit, u16 buttonSetId) {

	__asm {
		PUSHAD
		MOV EAX, unit
		MOV CX, buttonSetId
		CALL Func_Sub_4E5D60
		POPAD
	}

}



;

//This is what hide the infesting unit
const u32 Func_unitDeathSomething_0 = 0x004E6340;
void hideAndDisableUnit(CUnit* unit) {

	__asm {
		PUSHAD
		MOV EAX, unit
		CALL Func_unitDeathSomething_0
		POPAD
	  }

}

;

//What make the target reappear
const u32 Func_InitUnitTrapDoodad = 0x004E6490;
void showAndEnableUnit(CUnit* unit) {

  __asm {
    PUSHAD
    MOV EDI, unit
    CALL Func_InitUnitTrapDoodad
    POPAD
  }
}


;

//not related with assigning orders, but only with
//destinations of orders
const u32 Func_OrdersHoldPositionSuicidal = 0x004EB5B0;
void makeToHoldPosition(CUnit* unit) {

	__asm {
		PUSHAD
		MOV ESI, unit
		CALL Func_OrdersHoldPositionSuicidal
		POPAD
	}

}

;

} //Unnamed namespace

//End of helper functions
