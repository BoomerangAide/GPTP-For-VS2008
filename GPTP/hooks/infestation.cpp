#include "infestation.h"
#include <SCBW/api.h>
#include <SCBW/scbwdata.h>
#include <cassert>
#include "logger.h"

//Helper functions reusable

namespace scbw {

//helper reusable functions

const u32 Func_OrderReturnToIdle = 0x00463770;

void orderReturnToIdle(CUnit *unit) {

  assert(unit);

  __asm {
    PUSHAD
	MOV ESI, unit
    CALL Func_OrderReturnToIdle
    POPAD
  }

}

const u32 Func_Sub_464930 = 0x00464930;

//the name is a guess from the context
void disconnectFromAddOn(CUnit *unit) {

  assert(unit);

  __asm {
    PUSHAD
    MOV EAX, unit
    CALL Func_Sub_464930
    POPAD
  }

}

} //scbw

//-------- Helper function definitions. Do NOT modify! --------//

namespace {

const u32 Func_IncrementUnitDeathScores = 0x00488AF0;
void incrementDeathScores(const CUnit *unit, u8 player) {

  __asm {
    PUSHAD
    MOV EDI, unit
    MOVZX EDX, player
    CALL Func_IncrementUnitDeathScores
    POPAD
  }

}

const u32 Func_IncrementUnitScores = 0x00488BF0;
const u32 Func_IncrementUnitScoresEx = 0x00488D50;
void incrementUnitScores(const CUnit *unit, s8 value) {

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

const u32 Func_Sub_49EFA0 = 0x0049EFA0;
void readUnitsArray_Sub49EFA0(const CUnit *unit, u8 playerId) {

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

const u32 Func_Sub_49E4E0 = 0x0049E4E0;
void initializeEmptyUnitsLinkedListRef_Sub49E4E0(const CUnit *unit, u8 playerId) {

  __asm {

    PUSHAD

	MOV DL, playerId
	MOV ECX, unit

	CALL Func_Sub_49E4E0

    POPAD

  }

}

const u32 Func_RefundAllQueueSlots = 0x00466E80;
void refundAllQueueSlots(const CUnit *unit) {

  __asm {

    PUSHAD

	MOV EAX, unit
	CALL Func_RefundAllQueueSlots

    POPAD

  }

}

const u32 Func_removeOrderFromUnitQueue = 0x00004742D0;
void removeOrderFromUnitQueue(const CUnit *unit) {

  __asm {

    PUSHAD

	MOV ECX, unit
	CALL Func_removeOrderFromUnitQueue

    POPAD

  }

}

//code based on Func_Sub_4E5D60 related to RemoveOverlays
void reEnableUnit(CUnit *unit, u16 unitId) {

	//So many jump, it was hard to convert it into
	//something that make sense, this is the solution
	//I chose

	u8 jumpPoint = 0;

	if (!(unit->status & UnitStatus::InAir))
		jumpPoint = 1;

	if (jumpPoint == 0 && unit->lockdownTimer != 0)
		jumpPoint = 1;

	if (jumpPoint == 0 && unit->stasisTimer != 0)
		jumpPoint = 1;

	if (jumpPoint == 0 &&  unit->maelstromTimer == 0)
		jumpPoint = 2;

	if(jumpPoint != 0) {

		//original is "if byte ptr[ edx*4 + Starcraft.exe+264080 ] != 01"
		if ( (*(u8*)(0x00664080 + 4 * unitId)) != 1 )
			jumpPoint = 2;

		if(jumpPoint != 2 && unitId != UnitId::None)
			jumpPoint = 3;

	}

	if(jumpPoint != 3)
		unit->currentButtonSet = unit->id;

}

//Last commands in the orders_InfestMine1 function
//Absolutely no idea what this could be
void unknownInfestationLastCommands() {

	//offsets of functions needed in asm code
	const u32 someAdress1 = 0x0068C1B0;
	const u32 someAdress2 = 0x0068AC74;
	const u32 someAdress3 = 0x0068C1F8;
	const u32 someAdress4 = 0x0068C1E8;
	const u32 someAdress5 = 0x0068C1EC;

	__asm {
		PUSHAD
		XOR EAX, EAX
		MOV [someAdress1], 0x00000001
		MOV byte ptr[someAdress2], 0x01
		MOV byte ptr[someAdress3], 0x01
		MOV [someAdress4], EAX
		MOV [someAdress5], EAX
		POPAD
	}

}
} //Unnamed namespace

//End of helper functions

namespace hooks {

	bool unitCanInfest(const CUnit *unit) {

		bool returnValue; 

		returnValue = (unit->id == UnitId::queen || unit->id == UnitId::matriarch);

		return returnValue;

	}

	bool isInfestableUnit(const CUnit *unit) {

		u32 unitHpTest;
		u32 unitMaxHp;
		bool returnValue;

		returnValue = (unit->status & UnitStatus::Completed) /*&& (unit->id == UnitId::command_center)*/;

		if (returnValue) {

			unitMaxHp = unit->getMaxHpInGame();
			unitHpTest = unit->getCurrentHpInGame();

			//if HP/maxHP higher than 50%, not damaged enough
			if( ( (100 * unitHpTest) / unitMaxHp ) > 50 )
				returnValue = false;

		}

		return returnValue;

	}
	
	//Based on orders_InfestMine1 (0x004EA4C0)
	void orderMorphIntoInfested(CUnit *unitInfested, CUnit *unitInfesting) {

		bool bErrorReturnToIdle;
		bool bStopFunction = false;

		u16 infestedUnitNewId;
		u16 infestationOverlayId;

		bErrorReturnToIdle = (unitInfesting == NULL || !isInfestableUnit(unitInfested));

		GPTP::logger<<"part A"<<std::endl;

		if(!bErrorReturnToIdle) {

			if(unitInfested->mainOrderState == 0) {

				//init timer
				unitInfested->remainingBuildTime = 3;
				unitInfested->mainOrderState = 2;
				bStopFunction = true;

			}

			GPTP::logger<<"part B"<<std::endl;

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
					if(unitInfested->building.addon != NULL) {
						scbw::disconnectFromAddOn(unitInfested);
					}

					GPTP::logger<<"part C"<<std::endl;

					//this is the same as calling 0047B2E0 unitIsFactoryUnit like original code but faster 
					if(units_dat::GroupFlags[unitInfested->id].isFactory)
						unitInfested->rally.unit = unitInfested;

					//left like that, anybody would change that if using this file anyway
					infestedUnitNewId = /* *(u16*)(0x006648AC + 2*unitInfested->id); */ UnitId::ZergInfestedCommandCenter;

					//not infesting unit kills, maybe for global score?
					incrementDeathScores(unitInfested, unitInfesting->playerId);

					//structures destroyed applied to infested enemy (maybe change depending on unit type)
					incrementUnitScores(unitInfested, -1);

					//structures razed applied to infesting player (maybe change depending on unit type)
					incrementUnitScores(unitInfested, 1);

					GPTP::logger<<"part D"<<std::endl;

					//the unit receive the new id (infested id)
					unitInfested->id = infestedUnitNewId;

					//I don't really know, advanced internal mechanics, just have to work with it
					readUnitsArray_Sub49EFA0(unitInfested, unitInfesting->playerId);
					initializeEmptyUnitsLinkedListRef_Sub49E4E0(unitInfested, unitInfesting->playerId);

					//Related to infestation process
					unitInfested->setSecondaryOrder(0x17);

					GPTP::logger<<"part E"<<std::endl;

					//refund what the unit was producing
					refundAllQueueSlots(unitInfested);

					//clear the orders queue of the unit
					while(unitInfested->orderQueueHead != NULL)
						removeOrderFromUnitQueue(unitInfested);

					GPTP::logger<<"part F"<<std::endl;

					if(!(unitInfested->status & UnitStatus::GroundedBuilding)) {

						//Damn LIFO, to me it would be more natural if it was head
						CImage* current_image = unitInfested->sprite->images.tail;

						while(current_image != NULL) {

							//script 0x14 in asm code
							current_image->playIscriptAnim(IscriptAnimation::WorkingToIdle);

							//load next image of the list (or NULL)
							current_image = current_image->link.next;

						}

					}

					GPTP::logger<<"part G"<<std::endl;

					//Just use ImageId::InfestedCommandCenterOverlay instead 
					//if you're modding this file and you're going for the
					//default infestation overlay for any target.
					infestationOverlayId = *(u16*)(0x006610B0 + (unitInfested->id * 4));

					//asm would compare with hardcoded 999
					if(infestationOverlayId != ImageId::None)
						unitInfested->sprite->createOverlay(infestationOverlayId);

					GPTP::logger<<"part H"<<std::endl;

					//Assembly code is using
					//*(u16*)(0x00662350 + unitInfested->id)
					unitInfested->setHp(units_dat::MaxHitPoints[unitInfested->id]);

					//function named according to the content
					reEnableUnit(unitInfested,unitInfested->id);

					GPTP::logger<<"part I"<<std::endl;

					unknownInfestationLastCommands();

				} //if(unitInfested->remainingBuildTime == 0)

			} //if(!bStopFunction)

		} //if(!bErrorReturnToIdle)

		GPTP::logger<<"part J"<<std::endl;

		if(!bStopFunction)
			scbw::orderReturnToIdle(unitInfested);

		GPTP::logger<<"part K"<<std::endl;

	}

} //hooks
