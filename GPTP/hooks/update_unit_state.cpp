#include "update_unit_state.h"
#include "update_status_effects.h"
#include <SCBW/api.h>
#include <algorithm>

namespace {
//Helper function: Returns true if the unit's HP <= 33%.
bool unitHpIsInRedZone(CUnit* unit);					//0x004022C0
void RestoreAllUnitStats(CUnit* unit);					//0x00492F70 (hooked by hooks\update_status_effects.cpp)
void setAllImageGroupFlagsPal11(CSprite* sprite);		//0x00497430
} //unnamed namespace

namespace hooks {

/// This function regenerates energy for spellcasters and drains energy for
/// cloaking units.
/// Equivalent to function sub_4EB4B0 @ 0x004EB4B0
void updateUnitEnergy(CUnit* unit) {

	//was hardcoded instead of function calling in original code
	if (
		unit->isValidCaster() &&				//If the unit is hallucination or not a spellcaster, don't regenerate energy
		(unit->status & UnitStatus::Completed)	//If the unit is not fully constructed, don't regenerate energy
	)
	{

		bool bStopHere = false;

		//Spend energy for cloaked units
		if (
			unit->status & (UnitStatus::Cloaked + UnitStatus::RequiresDetection) &&	//If the unit is cloaked
			!(unit->status & UnitStatus::CloakingForFree)						//...and must consume energy to stay cloaked (i.e. not under an Arbiter)
		)
		{

			u16 cloakingEnergyCost;

			//Equivalent to getCloakingEnergyConsumption @ 0x00491A90
			if (unit->id == UnitId::TerranGhost ||
				unit->id == UnitId::Hero_SarahKerrigan ||
				unit->id == UnitId::Hero_InfestedKerrigan ||
				unit->id == UnitId::Hero_SamirDuran ||
				unit->id == UnitId::Hero_InfestedDuran ||
				unit->id == UnitId::Hero_AlexeiStukov
			)
				cloakingEnergyCost = 10;
			else 
			if (unit->id == UnitId::TerranWraith ||
				unit->id == UnitId::Hero_TomKazansky
			)
				cloakingEnergyCost = 13;
			else
				cloakingEnergyCost = 0;

			if (!(unit->hasEnergy(cloakingEnergyCost)))
			{

				if (unit->secondaryOrderId == OrderId::Cloak)
					unit->setSecondaryOrder(OrderId::Nothing2); //Supposedly, immediately decloaks the unit.

				bStopHere = true;

			}

			if(!bStopHere)	//the function prevent energy consumption if THE GATHERING enabled
				unit->spendUnitEnergy(cloakingEnergyCost);

		}
		else { //EB526

			int maxEnergy;

			if (unit->id == UnitId::ProtossDarkArchon &&
				unit->mainOrderId == OrderId::CompletingArchonSummon &&
				unit->mainOrderState == 0
			)
				maxEnergy = 12800;  //50 * 256; Identical to energy amount on spawn
			else
				maxEnergy = unit->getMaxEnergy();

			if(unit->energy == maxEnergy)
				bStopHere = true;
			else {

				unit->energy += 8;

				//Omitting hardcoded recalculation of maxEnergy

				//Omitting recalculation of maxEnergy through
				//GetDarkArchonEnergy @ 0x00491C00 since it
				//calculate maxEnergy the same way the previous
				//code did, and nothing could have changed the
				//parameters used since the calculation
				if(unit->energy > maxEnergy)
					unit->energy = maxEnergy;

			}

		}

		//If the unit is currently selected, redraw its graphics
		if (!bStopHere && unit->sprite->flags & CSprite_Flags::Selected)
			setAllImageGroupFlagsPal11(unit->sprite);

	}

} 

/// Updates unit timers, regenerates hp and shields, and burns down Terran buildings.
/// Identical to function @ 0x004EC290
void updateUnitStateHook(CUnit* unit) {

	//Timers
	if (unit->mainOrderTimer)
		unit->mainOrderTimer--;
	if (unit->groundWeaponCooldown)
		unit->groundWeaponCooldown--;
	if (unit->airWeaponCooldown)
		unit->airWeaponCooldown--;
	if (unit->spellCooldown)
		unit->spellCooldown--;

	//Shield regeneration
	if (units_dat::ShieldsEnabled[unit->id] != 0) {

		s32 maxShields = (s32)(units_dat::MaxShieldPoints[unit->id]) * 256;

		if (unit->shields != maxShields) {

			unit->shields += 7;

			if (unit->shields > maxShields)
				unit->shields = maxShields;

			if (unit->sprite->flags & CSprite_Flags::Selected)  //If the unit is currently selected, redraw its graphics
				setAllImageGroupFlagsPal11(unit->sprite);

		}

	}

	//Supposedly, allows Zerglings to attack after unburrowing without delay.
	if (unit->id == UnitId::zergling || unit->id == UnitId::Hero_DevouringOne)
		if (unit->groundWeaponCooldown == 0)
		  unit->orderQueueTimer = 0;

	//Clear the healing flag every frame
	unit->isBeingHealed = 0;

	//Update unit status effects (stim, maelstrom, plague, etc.)
	if (unit->status & UnitStatus::Completed || !(unit->sprite->flags & CSprite_Flags::Hidden)) {

		unit->cycleCounter++;

		if (unit->cycleCounter >= 8) {
			unit->cycleCounter = 0;
			RestoreAllUnitStats(unit); //use update_status_effects hook if available
		}

	}

	//Only for fully-constructed units and buildings
	if (unit->status & UnitStatus::Completed) {

		bool bStopHere = false;

		//HP regeneration
		if (
			units_dat::BaseProperty[unit->id] & UnitProperty::RegeneratesHP &&
			unit->hitPoints > 0 &&
			unit->hitPoints != units_dat::MaxHitPoints[unit->id]
		)
			unit->setHp(unit->hitPoints + 4);

		//Update unit energy (energy regen/drain)
		//call StarCraft.exe+EB4B0		//sub_4EB4B0
		updateUnitEnergy(unit);

		//Recent order timer
		if (unit->recentOrderTimer != 0)
			unit->recentOrderTimer--;

		//Self-destruct timer
		if (unit->removeTimer != 0) {

			unit->removeTimer--;

			if (unit->removeTimer == 0) {
				unit->remove();
				bStopHere = true;
			}

		}

		//Terran building burn-down
		if (!bStopHere) {

			RaceId::Enum raceId = unit->getRace();

			if(
				raceId != RaceId::Zerg &&
				raceId != RaceId::Protoss &&
				raceId == RaceId::Terran
			)

				//Check if the unit is a grounded or lifted building
				if (	
					unit->status & UnitStatus::GroundedBuilding ||
					units_dat::BaseProperty[unit->id] & UnitProperty::FlyingBuilding)
				{

					//...whose current HP is less or equal to 33% of max HP
					if (unitHpIsInRedZone(unit))
						unit->damageHp(20, NULL, unit->lastAttackingPlayer,true);

				}

		} //if (unit->getRace() == RaceId::Terran)


	} //if (unit->status & UnitStatus::Completed) {

}

//StarCraft.exe+EC290- push esi
//StarCraft.exe+EC291- mov esi,eax				//ESI = unit
//StarCraft.exe+EC293- mov al,[esi+54]			//AL = unit->mainOrderTimer
//StarCraft.exe+EC296- test al,al				//if(unit->mainOrderTimer == 0)
//StarCraft.exe+EC298- je StarCraft.exe+EC29F	//jump

//StarCraft.exe+EC29A- dec al					
//StarCraft.exe+EC29C- mov [esi+54],al			//unit->mainOrderTimer--

//EC29F:

//StarCraft.exe+EC29F- mov al,[esi+55]			//AL = unit->groundWeaponCooldown
//StarCraft.exe+EC2A2- test al,al
//StarCraft.exe+EC2A4- je StarCraft.exe+EC2AB	//if(unit->groundWeaponCooldown == 0) jump

//StarCraft.exe+EC2A6- dec al
//StarCraft.exe+EC2A8- mov [esi+55],al			//unit->groundWeaponCooldown--

//EC2AB:

//StarCraft.exe+EC2AB- mov al,[esi+56]
//StarCraft.exe+EC2AE- test al,al
//StarCraft.exe+EC2B0- je StarCraft.exe+EC2B7

//StarCraft.exe+EC2B2- dec al
//StarCraft.exe+EC2B4- mov [esi+56],al			//unit->airWeaponCooldown--

//EC2B7:

//StarCraft.exe+EC2B7- mov al,[esi+57]
//StarCraft.exe+EC2BA- test al,al
//StarCraft.exe+EC2BC- je StarCraft.exe+EC2C3

//StarCraft.exe+EC2BE- dec al
//StarCraft.exe+EC2C0- mov [esi+57],al			//unit->spellCooldown--;

//EC2C3:

//StarCraft.exe+EC2C3- movzx eax,word ptr [esi+64]			//EAX = unit->id
//StarCraft.exe+EC2C7- mov cl,[eax+StarCraft.exe+2647B0]	//CL = units_dat::ShieldsEnabled[unit->id]
//StarCraft.exe+EC2CD- test cl,cl
//StarCraft.exe+EC2CF- je StarCraft.exe+EC2FE				//if not jump

//StarCraft.exe+EC2D1- movzx eax,word ptr [eax*2+StarCraft.exe+260E00]	//EAX = units_dat::MaxShieldPoints[unit->id]
//StarCraft.exe+EC2D9- mov ecx,[esi+60]									//ECX = unit->shields
//StarCraft.exe+EC2DC- shl eax,08										//EAX = units_dat::MaxShieldPoints[unit->id] * 256
//StarCraft.exe+EC2DF- cmp ecx,eax
//StarCraft.exe+EC2E1- je StarCraft.exe+EC2FE							//if(unit->shields == units_dat::MaxShieldPoints[unit->id] / 256) jump

//StarCraft.exe+EC2E3- add ecx,07				//ECX = unit->shields + 7
//StarCraft.exe+EC2E6- cmp ecx,eax				
//StarCraft.exe+EC2E8- mov [esi+60],ecx			//unit->shields += 7
//StarCraft.exe+EC2EB- jle StarCraft.exe+EC2F0	//if(unit->shields + 7 <= units_dat::MaxShieldPoints[unit->id] / 256) jump

//StarCraft.exe+EC2ED- mov [esi+60],eax			//unit->shields = units_dat::MaxShieldPoints[unit->id] / 256

//EC2F0:

//StarCraft.exe+EC2F0- mov eax,[esi+0C]				//EAX = unit->sprite
//StarCraft.exe+EC2F3- test byte ptr [eax+0E],08	//if(!(unit->sprite->flags & CSprite_Flags::Selected))
//StarCraft.exe+EC2F7- je StarCraft.exe+EC2FE		//jump

//StarCraft.exe+EC2F9- call StarCraft.exe+97430		//setAllImageGroupFlagsPal11

//EC2FE:

//StarCraft.exe+EC2FE- mov ax,[esi+64]			//AX = unit->id
//StarCraft.exe+EC302- cmp ax,0025				//if(unit->id == UnitId::ZergZergling
//StarCraft.exe+EC306- je StarCraft.exe+EC30E	//jump

//StarCraft.exe+EC308- cmp ax,0036				//if(unit->id == UnitId::Hero_DevouringOne
//StarCraft.exe+EC30C- jne StarCraft.exe+EC31C	//continue

//EC30E:

//StarCraft.exe+EC30E- mov al,[esi+55]			//AL = unit->groundWeaponCooldown
//StarCraft.exe+EC311- test al,al
//StarCraft.exe+EC313- jne StarCraft.exe+EC31C	//if(unit->groundWeaponCooldown != 0) jump

//StarCraft.exe+EC315- mov byte ptr [esi+00000085],00	//unit->orderQueueTimer = 0

//EC31C:

//StarCraft.exe+EC31C- test byte ptr [esi+000000DC],01
//StarCraft.exe+EC323- mov byte ptr [esi+00000107],00	//unit->isBeingHealed = 0
//StarCraft.exe+EC32A- jne StarCraft.exe+EC335			//if(unit->status & UnitStatus::Completed) jump

//StarCraft.exe+EC32C- mov eax,[esi+0C]				//EAX = unit->sprite
//StarCraft.exe+EC32F- test byte ptr [eax+0E],20	//if(unit->sprite->flags & CSprite_Flags::Hidden)
//StarCraft.exe+EC333- jne StarCraft.exe+EC357		//jump

//EC335:

//StarCraft.exe+EC335- mov cl,[esi+00000122]		//CL = unit->cycleCounter
//StarCraft.exe+EC33B- inc cl						//CL = unit->cycleCounter + 1
//StarCraft.exe+EC33D- mov al,cl					//AL = CL
//StarCraft.exe+EC33F- cmp al,08
//StarCraft.exe+EC341- mov [esi+00000122],cl		//unit->cycleCounter = unit->cycleCounter + 1
//StarCraft.exe+EC347- jb StarCraft.exe+EC357		//if(newCycleCounter < 8) jump

//StarCraft.exe+EC349- mov eax,esi						//EAX = unit
//StarCraft.exe+EC34B- mov byte ptr [esi+00000122],00	//unit->cycleCounter = 0
//StarCraft.exe+EC352- call StarCraft.exe+92F70			//RestoreAllUnitStats

//EC357:

//StarCraft.exe+EC357- test byte ptr [esi+000000DC],01		//if(!(unit->status & UnitStatus::Completed))
//StarCraft.exe+EC35E- je StarCraft.exe+EC410				//jump to end

//StarCraft.exe+EC364- movzx ecx,word ptr [esi+64]			//ECX = unit->id
//StarCraft.exe+EC368- shl ecx,02
//StarCraft.exe+EC36B- mov al,[ecx+StarCraft.exe+264080]	//AL = units_dat::BaseProperty[unit->id]
//StarCraft.exe+EC371- test al,al							//if(!(units_dat::BaseProperty[unit->id] == UnitProperty::RegeneratesHP))
//StarCraft.exe+EC373- jns StarCraft.exe+EC38E				//jump

//StarCraft.exe+EC375- mov eax,[esi+08]			//EAX = unit->hitPoints
//StarCraft.exe+EC378- test eax,eax				//if(unit->hitPoints <= 0
//StarCraft.exe+EC37A- jle StarCraft.exe+EC38E	//jump

//StarCraft.exe+EC37C- cmp eax,[ecx+StarCraft.exe+262350]	//if(unit->hitPoints == units_dat::MaxHitPoints[unit->id]
//StarCraft.exe+EC382- je StarCraft.exe+EC38E				//jump

//StarCraft.exe+EC384- lea ecx,[eax+04]				//ECX = unit->hitPoints + 4
//StarCraft.exe+EC387- mov eax,esi					//EAX = unit
//StarCraft.exe+EC389- call StarCraft.exe+67340		//setUnitHP

//EC38E:

//StarCraft.exe+EC38E- call StarCraft.exe+EB4B0		//sub_4EB4B0

//StarCraft.exe+EC393- mov al,[esi+000000E3]	//AL = unit->recentOrderTimer
//StarCraft.exe+EC399- test al,al
//StarCraft.exe+EC39B- je StarCraft.exe+EC3A5	//if(unit->recentOrderTimer == 0) jump

//StarCraft.exe+EC39D- dec al					
//StarCraft.exe+EC39F- mov [esi+000000E3],al	//unit->recentOrderTimer--

//EC3A5:

//StarCraft.exe+EC3A5- xor eax,eax				//EAX = 0
//StarCraft.exe+EC3A7- mov ax,[esi+00000110]	//AX = unit->removeTimer
//StarCraft.exe+EC3AE- test ax,ax
//StarCraft.exe+EC3B1- je StarCraft.exe+EC3C8	//if(unit->removeTimer == 0) jump

//StarCraft.exe+EC3B3- dec eax					//EAX = unit->removeTimer - 1
//StarCraft.exe+EC3B4- test ax,ax
//StarCraft.exe+EC3B7- mov [esi+00000110],ax	//unit->removeTimer = unit->removeTimer - 1
//StarCraft.exe+EC3BE- jne StarCraft.exe+EC3C8	//if(unit->removeTimer != 0) jump

//StarCraft.exe+EC3C0- mov eax,esi					//EAX = unit
//StarCraft.exe+EC3C2- pop esi
//StarCraft.exe+EC3C3- jmp StarCraft.exe+75710		//orders_SelfDestructing

//EC3C8:

//StarCraft.exe+EC3C8- movzx ecx,word ptr [esi+64]			//ECX = unit->id
//StarCraft.exe+EC3CC- mov al,[ecx+StarCraft.exe+2637A0]	//AL = units_dat::GroupFlags[unit->id]
//StarCraft.exe+EC3D2- test al,05							//if(units_dat::GroupFlags[unit->id].isProtoss || units_dat::GroupFlags[unit->id].isZerg)
//StarCraft.exe+EC3D4- jne StarCraft.exe+EC410				//jump to end

//StarCraft.exe+EC3D6- test al,02							//if(!units_dat::GroupFlags[unit->id].isTerran)
//StarCraft.exe+EC3D8- je StarCraft.exe+EC410				//jump to end

//StarCraft.exe+EC3DA- test byte ptr [esi+000000DC],02	//if(unit->status & GroundedBuilding)
//StarCraft.exe+EC3E1- jne StarCraft.exe+EC3ED			//jump

//StarCraft.exe+EC3E3- test byte ptr [ecx*4+StarCraft.exe+264080],20	//if(!(units_dat::BaseProperty[unit->id] & FlyingBuilding))
//StarCraft.exe+EC3EB- je StarCraft.exe+EC410							//jump to end

//EC3ED:

//StarCraft.exe+EC3ED- mov ecx,esi					//ECX = unit
//StarCraft.exe+EC3EF- call StarCraft.exe+22C0		//unitHPbelow33_percent

//StarCraft.exe+EC3F4- test eax,eax					//if(no)
//StarCraft.exe+EC3F6- je StarCraft.exe+EC410		//jump to end

//StarCraft.exe+EC3F8- movzx ecx,byte ptr [esi+00000090]	//ECX = unit->lastAttackingPlayer
//StarCraft.exe+EC3FF- push 01						//PUSH 01
//StarCraft.exe+EC401- push ecx						//PUSH unit->lastAttackingPlayer
//StarCraft.exe+EC402- push 00						//PUSH 00
//StarCraft.exe+EC404- mov eax,00000014				//EAX = 20 (0x14)
//StarCraft.exe+EC409- mov ecx,esi					//ECX = unit
//StarCraft.exe+EC40B- call StarCraft.exe+797B0		//killTargetUnitCheck

//EC410:

//StarCraft.exe+EC410- pop esi
//StarCraft.exe+EC411- ret 

} //hooks

namespace {

/**** Helper function definitions. Do not modify anything below this! ****/

const u32 Helper_UnitHpIsInRedZone  = 0x004022C0;
bool unitHpIsInRedZone(CUnit* unit) {

  static Bool32 result;

	__asm {
		PUSHAD
		MOV ECX, unit
		CALL Helper_UnitHpIsInRedZone
		MOV result, EAX
		POPAD
	}

	return result != 0;
}

;

//hooked by hooks\update_status_effects.cpp
const u32 Func_RestoreAllUnitStats = 0x00492F70;
void RestoreAllUnitStats(CUnit* unit) {

	__asm {
		PUSHAD
		MOV EAX, unit
		CALL Func_RestoreAllUnitStats
		POPAD
	}

}

;

//Identical to setAllImageGroupFlagsPal11 @ 0x00497430;
void setAllImageGroupFlagsPal11(CSprite* sprite) {

	for(
		CImage* current_image = sprite->images.head; 
		current_image != NULL;
		current_image = current_image->link.next
	)
	{
		if(current_image->paletteType == PaletteType::RLE_HPFLOATDRAW)
			current_image->flags |= CImage_Flags::Redraw;
	}

}

;

}
