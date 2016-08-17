#include "spider_mine.h"
#include <SCBW/api.h>
#include <SCBW/UnitFinder.h>

//helper functions def
namespace {
	CUnit* SpiderMine_AcquireTarget(CUnit* spiderMine);	//0x00441270
	void function_00495400(CUnit* unit, CUnit* target);	//0x00495400
	void function_0049B1E0(CUnit* unit);				//0x0049B1E0
	void function_004E99D0(CUnit* unit);				//0x004E99D0
	void function_004E9A30(CUnit* unit);				//0x004E9A30
	void setNextWaypoint_Sub4EB290(CUnit* unit);		//0x004EB290
} //unnamed namespace

//Helper class for findBestSpiderMineTargetHook()
//Equivalent to 00440EC0  SpiderMine_EnemyProc
class SpiderMineTargetFinder: public scbw::UnitFinderCallbackMatchInterface {

  CUnit* spiderMine;

  public:
    //Check if @p unit is a suitable target for the @p spiderMine.
    bool match(CUnit* target) {

		//Don't attack friendly / allied units
		if (!spiderMine->isTargetEnemy(target))
			return false;

		//Don't attack invincible units
		if (target->status & UnitStatus::Invincible)
			return false;

		//Don't attack air units / buildings
		if (target->status & (UnitStatus::InAir | UnitStatus::GroundedBuilding))
			return false;

		//Don't attack hovering units
		if (units_dat::MovementFlags[target->id] == MovementFlags::HoverUnit)
			return false;

		return true;

    }

    //Constructor
    SpiderMineTargetFinder(CUnit* spiderMine) : spiderMine(spiderMine) {}
};

//StarCraft.exe+40EC0- mov al,[ecx+4C]			//AL = target->playerId
//StarCraft.exe+40EC3- cmp al,0B				
//StarCraft.exe+40EC5- mov dl,[edx+4C]			//DL = unit->playerId
//StarCraft.exe+40EC8- jne StarCraft.exe+40ED0	//if(target->playerId != 11) jump

//StarCraft.exe+40ECA- mov eax,[ecx+0C]			//EAX = target->sprite
//StarCraft.exe+40ECD- mov al,[eax+0A]			//AL = target->sprite->playerId

//40ED0:

//StarCraft.exe+40ED0- movzx edx,dl								//...
//StarCraft.exe+40ED3- movzx eax,al								//...
//StarCraft.exe+40ED6- push ebx									//...
//StarCraft.exe+40ED7- lea edx,[edx+edx*2]						//...
//StarCraft.exe+40EDA- mov bl,[eax+edx*4+StarCraft.exe+18D634]	//BL = playerAlliance[unit->playerId].flags[targetOwnerId]
//StarCraft.exe+40EE1- test bl,bl
//StarCraft.exe+40EE3- pop ebx
//StarCraft.exe+40EE4- jne StarCraft.exe+40F0A					//if(allied) jump to return false

//StarCraft.exe+40EE6- mov eax,[ecx+000000DC]					
//StarCraft.exe+40EEC- test eax,04000000						//if target invincible jump

//StarCraft.exe+40EF1- jne StarCraft.exe+40F0A

//StarCraft.exe+40EF3- test al,06
//StarCraft.exe+40EF5- jne StarCraft.exe+40F0A					//if(target GroundedBuilding+InAir return false

//StarCraft.exe+40EF7- movzx ecx,word ptr [ecx+64]
//StarCraft.exe+40EFB- cmp byte ptr [ecx+StarCraft.exe+260FC8],-3F	if(hover return false
//StarCraft.exe+40F02- je StarCraft.exe+40F0A

//StarCraft.exe+40F04- mov eax,00000001
//StarCraft.exe+40F09- ret 

//40F0A:

//StarCraft.exe+40F0A- xor eax,eax
//StarCraft.exe+40F0C- ret 

namespace hooks {

const int SPIDERMINE_BURROW_TIME = 60;
const int SPIDERMINE_SEEKING_RANGE = 576;
const int SPIDERMINE_DETONATE_RANGE = 30;

//Return the best target for the Spider Mine. If there is no suitable target,
//return NULL instead.
CUnit* findBestSpiderMineTargetHook(CUnit* spiderMine) {

	//Default StarCraft behavior
	s32 range;

	//Don't search for a target if the spider mine is under a Disruption Web
	if (spiderMine->status & UnitStatus::CanNotAttack)
		return NULL;

	range = 32 * spiderMine->getSeekRange();

	return 
		scbw::UnitFinder::getNearestTarget(
			spiderMine->getX() - range, spiderMine->getY() - range,
			spiderMine->getX() + range, spiderMine->getY() + range,
			spiderMine, SpiderMineTargetFinder(spiderMine)
		);

}

;

void orders_VultureMine(CUnit* unit) {

	if(unit->mainOrderState == 0) {
		unit->groundWeaponCooldown = SPIDERMINE_BURROW_TIME;
		unit->mainOrderState = 1;
	}

	if(unit->mainOrderState == 1) {
		
		if(unit->groundWeaponCooldown == 0) {
			unit->sprite->playIscriptAnim(IscriptAnimation::Burrow,true);
			unit->status |= UnitStatus::NoCollide;
			unit->mainOrderState = 2;
		}

	}

	if(unit->mainOrderState == 2) {

		if(!(unit->orderSignal & 4)) {

			if(!(unit->status & UnitStatus::IsHallucination)) {
				function_004E9A30(unit); //related to movement
				function_0049B1E0(unit); //related to cloaking/stealth
			}

			unit->mainOrderState = 3;

		}

	}

	if(unit->mainOrderState == 3) {

		CUnit* target = SpiderMine_AcquireTarget(unit);

		if(target != NULL) {

			unit->orderTarget.unit = target;

			unit->sprite->playIscriptAnim(IscriptAnimation::UnBurrow,true);

			//disable burrowed flag if still on
			unit->sprite->flags &= ~CSprite_Flags::Burrowed;

			//might have been some cloaking order before
			unit->setSecondaryOrder(OrderId::Nothing2);

			unit->mainOrderState = 4;

		}

	}

	if(unit->mainOrderState == 4) {

		if(unit->orderSignal & 4) {

			unit->sprite->elevationLevel = units_dat::Elevation[unit->id];
			
			//disabled NoCollide flag if was still on
			unit->status &= ~UnitStatus::NoCollide;

			if(unit->orderTarget.unit != NULL) {

				//probably trigger movement/acceleration of unit
				//toward the target
				function_00495400(unit,unit->orderTarget.unit);

				unit->mainOrderState = 5;

			}
			else
				unit->mainOrderState = 1;

		}

	}
	else //unlike the previous states, going directly from state 4 to 5 in the same frame is impossible
	if(unit->mainOrderState == 5) {

		bool bIsCompletelyInRange = false;
		bool bEndThere = false;

		function_004E99D0(unit); //related to movement, similar to function_004E9A30

		if(unit->orderTarget.unit != NULL) {

			if(unit->isTargetWithinMinRange(unit->orderTarget.unit,SPIDERMINE_SEEKING_RANGE)) {

				//probably trigger movement/acceleration of unit
				//toward the target
				function_00495400(unit,unit->orderTarget.unit);

				if(unit->isTargetWithinMinRange(unit->orderTarget.unit,SPIDERMINE_DETONATE_RANGE))
					bIsCompletelyInRange = true; //jump to 63F22
				else
				if(unit->getMovableState() != 2)
					bEndThere = true;

			}

		}

		if(!bEndThere) { //63F14
			setNextWaypoint_Sub4EB290(unit);
			unit->mainOrderState = 1;
		}

		if(bIsCompletelyInRange) { //63F22

			CImage* current_image;

			unit->orderTarget.unit = NULL;
			unit->orderTarget.pt.x = unit->sprite->position.x;
			unit->orderTarget.pt.y = unit->sprite->position.y;

			current_image = unit->sprite->images.head;

			while(current_image != NULL) {
				current_image->playIscriptAnim(IscriptAnimation::SpecialState1);
				current_image = current_image->link.next;
			}

			unit->mainOrderState = 6;
			
		}

	}

	//unlike state 5 with state 4, state 6 can be chained from
	//state 5, so no else here
	if(unit->mainOrderState == 6) {
		if(unit->orderSignal & 1) {
			unit->remove();
		}
	}
	
}

;

} //hooks

;

//-------- Helper function definitions. Do NOT modify! --------//

namespace {

CUnit* SpiderMine_AcquireTarget(CUnit* spiderMine) {

	const u32 Func_SpiderMine_AcquireTarget = 0x00441270;
	
	static CUnit* target;

	__asm {
		PUSHAD
		MOV ESI, spiderMine
		CALL Func_SpiderMine_AcquireTarget
		MOV target, EAX
		POPAD
	}

	return target;

}

;

const u32 Func_Sub495400 = 0x00495400;
void function_00495400(CUnit* unit, CUnit* target) {

	__asm {
		PUSHAD
		MOV EDI, unit
		MOV EAX, target
		CALL Func_Sub495400
		POPAD
	}

}

;

void function_0049B1E0(CUnit* unit) {

	const u32 Func_Sub49B1E0 = 0x0049B1E0;

	__asm {
		PUSHAD
		MOV EDI, unit
		CALL Func_Sub49B1E0
		POPAD
	}

}

;

void function_004E99D0(CUnit* unit) {

	const u32 Func_Sub4E99D0 = 0x004E99D0;

	__asm {
		PUSHAD
		MOV EAX, unit
		CALL Func_Sub4E99D0
		POPAD
	}

}

;

void function_004E9A30(CUnit* unit) {

	const u32 Func_Sub4E9A30 = 0x004E9A30;

	__asm {
		PUSHAD
		MOV EAX, unit
		CALL Func_Sub4E9A30
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

} //Unnamed namespace

//End of helper functions
