#include "feedback_spell.h"
#include <SCBW/api.h>

//helper functions def

namespace {

u8 hasOverlay(CUnit* unit);																							//7B720
bool ordersSpell_Sub_4926D0(CUnit* unit, u32 techId, u16* techEnergyCost, u32 sightRange,u32 error_message_index);	//926D0
void replaceFeedbackSprite(CUnit* unit, u32 spriteId);																//F6350

} //unnamed namespace

namespace hooks {

void orders_Feedback(CUnit* unit) {

	CUnit* target = unit->orderTarget.unit;

	if(
		target != NULL &&
		units_dat::BaseProperty[target->id] & UnitProperty::Spellcaster &&
		!(target->status & UnitStatus::IsHallucination)
	) 
	{

		u16 techCost;
		int sightRange = unit->getSightRange(true);

		if(
			ordersSpell_Sub_4926D0(
				unit,
				TechId::Feedback,
				&techCost,
				sightRange * 32,
				0x532 //Must target units with energy
			)
		)
		{

			if(target->status & UnitStatus::IsHallucination) {
				u8 overlaySize = hasOverlay(target);
				replaceFeedbackSprite(target,overlaySize + SpriteId::Feedback_Hit_Small);
				unit->spendUnitEnergy(techCost);
				target->remove();
				unit->orderToIdle();
			}
			else { //F6DE3

				if(target->energy <= 0)
					unit->orderToIdle();
				else {

					target->damageWith(target->energy,WeaponId::Feedback,unit,unit->playerId,1,1);
					target->energy = 0;
					unit->spendUnitEnergy(techCost);
					scbw::playSound(SoundId::Protoss_Darchon_feedback_wav,target);

					if(!target->isDead()) {

						u8 overlaySize = hasOverlay(target);

						if(target->subunit != NULL)
							target->subunit->sprite->createTopOverlay(overlaySize + ImageId::Feedback_Small,0,0,0);
						else
							target->sprite->createTopOverlay(overlaySize + ImageId::Feedback_Small,0,0,0);

						unit->orderToIdle();

					}
					else { //F6E6D
						u8 overlaySize = hasOverlay(target);
						replaceFeedbackSprite(target,overlaySize + SpriteId::Feedback_Hit_Small);
						unit->orderToIdle();
					}

				}

			}

		}


	}
	else {	//F6E92

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

} //namespace hooks

;

//-------- Helper function definitions. Do NOT modify! --------//

namespace {

const u32 Func_hasOverlay = 0x0047B720;
u8 hasOverlay(CUnit* unit) {

	static u8 result;

	__asm {
		PUSHAD
		MOV EAX, unit
		CALL Func_hasOverlay
		MOV result, AL
		POPAD
	}

	return result;

}

;

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

const u32 Func_replaceFeedbackSprite = 0x004F6350;
void replaceFeedbackSprite(CUnit* unit, u32 spriteId) {

	__asm {
		PUSHAD
		MOV EBX, unit
		PUSH spriteId
		CALL Func_replaceFeedbackSprite
		POPAD
	}

}

;

} //Unnamed namespace

//End of helper functions
