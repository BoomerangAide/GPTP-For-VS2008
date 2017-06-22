#include "recall_spell.h"
#include <SCBW/api.h>

//helper functions def

namespace {

bool ordersSpell_Sub_4926D0(CUnit* unit, u32 techId, u16* techEnergyCost, u32 sightRange,u32 error_message_index);	//926D0
void UnitDestructor(CUnit* unit);																					//A0990
bool function_004F66D0(CUnit* unit);																				//F66D0
CUnit* createHallucinationUnit(CUnit* target, u32 playerId);														//F6B90


} //unnamed namespace

namespace hooks {

	void orders_Hallucination1(CUnit* unit) {

		int sightRange = unit->getSightRange(true);
		u16 techCost;

		if(
			ordersSpell_Sub_4926D0(
				unit,
				TechId::Hallucination,
				&techCost,
				sightRange * 32,
				0x899 //Invalid Target
			)
		)
		{

			int counter = 2;

			while(counter > 0) {

				counter--;

				CUnit* hal_unit = createHallucinationUnit(unit->orderTarget.unit,unit->playerId);

				if(hal_unit == NULL)
					counter = 0;
				else
				if(!function_004F66D0(hal_unit)) {
					counter = 0;
					UnitDestructor(hal_unit);
				}

			}

			if(!(*CHEAT_STATE & CheatFlags::TheGathering))
				unit->energy -= techCost;

			scbw::playSound(SoundId::Protoss_TEMPLAR_PTeHal00_WAV,unit->orderTarget.unit);

			if(unit->orderTarget.unit->subunit != NULL)
				unit->orderTarget.unit->subunit->sprite->createOverlay(ImageId::HallucinationHit,0,0,0);
			else
				unit->orderTarget.unit->sprite->createOverlay(ImageId::HallucinationHit,0,0,0);

			if(unit->orderQueueHead != NULL) {
				unit->userActionFlags |= 1;
				prepareForNextOrder(unit);
			}
			else
			if(unit->pAI != NULL)
				unit->orderComputerCL(OrderId::ComputerAI);
			else
				unit->orderComputerCL(units_dat::ReturnToIdleOrder[unit->id]);

		}

	}

	;

} //namespace hooks

;

//-------- Helper function definitions. Do NOT modify! --------//

namespace {

const u32 Func_Sub_4926D0 = 0x004926D0;
bool ordersSpell_Sub_4926D0(CUnit* unit, u32 techId, u16* techEnergyCost, u32 sightRange,u32 error_message_index) {

	static Bool32 bPreResult;

	__asm {
		PUSHAD
		PUSH techEnergyCost
		PUSH sightRange
		PUSH techId
		MOV EAX, error_message_index
		MOV EBX, unit
		CALL Func_Sub_4926D0
		MOV bPreResult, EAX
		POPAD
	}

	return (bPreResult != 0);

}

;

const u32 Func_UnitDestructor = 0x004A0990;
void UnitDestructor(CUnit* unit) {

	__asm {
		PUSHAD
		MOV ECX, unit
		CALL Func_UnitDestructor
		POPAD
	}

}

;

const u32 Func_sub_4F66D0 = 0x004F66D0;
bool function_004F66D0(CUnit* unit) {

	static Bool32 bPreResult;

	__asm {
		PUSHAD
		MOV EAX, unit
		CALL Func_sub_4F66D0
		MOV bPreResult, EAX
		POPAD
	}

	return (bPreResult != 0);

}

;

const u32 Func_sub_4F6B90 = 0x004F6B90;
CUnit* createHallucinationUnit(CUnit* target, u32 playerId) {

	static CUnit* return_value;

	__asm {
		PUSHAD
		PUSH playerId
		MOV ECX, target
		CALL Func_sub_4F6B90
		MOV return_value, EAX
		POPAD
	}

	return return_value;

}

;


} //Unnamed namespace

//End of helper functions
