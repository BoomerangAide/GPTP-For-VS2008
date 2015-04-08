#include "helpfunc.h"

namespace helpers {

	const u32 Func_FixTargetLocation =						0x00401FA0;
	const u32 Func_HideDialog =								0x00418700;
	const u32 Func_Sub_42D9A0_IsVisible =					0x0042D9A0;
	const u32 Func_SetRepulseAngle =						0x00453300;
	const u32 Func_RemoveRepulseTile =						0x004533D0;
	const u32 Func_ApplySpeedUpgradeFromUnitType =			0x00454370;
	const u32 Func_Sub_463040_AI_PlaceGuard =				0x00463040;
	const u32 Func_Sub_469EC0_SortLeftRight =				0x00469EC0;
	const u32 Func_Sub_469F60_SortLeftRight =				0x00469F60;
	const u32 Func_SortUnit =								0x0046A300;
	const u32 Func_UpdateUnitOrderFinder =					0x0046A3A0;
	const u32 Func_Sub_476D30_DoWeaponIscript =				0x00476D30;
	const u32 Func_Sub_47CB90_NameTooLongToBePutHere =		0x0047CB90;
	const u32 Func_IncrementUnitScores =					0x00488BF0;
	const u32 Func_IncrementUnitScoresEx =					0x00488D50;
	const u32 Func_ClearUnitTarget =						0x0048AAC0;
	const u32 Func_PlayBuildingLiftoffSound =				0x0048F8A0;
	const u32 Func_GetFlingyHaltDistance =					0x00494F90;
	const u32 Func_Sub_497480_GetSpriteUnderlay =			0x00497480;
	const u32 Func_Sub_49A7F0_CompareUnitRank =				0x0049A7F0;
	const u32 Func_Sub_49DE50_AirTrainingProc =				0x0049DE50;
	const u32 Func_Sub_49DEA0_AirTrainingProc =				0x0049DEA0;
	const u32 Func_Sub_49EFA0_ReadUnitsArray =				0x0049EFA0;
	const u32 Func_Sub_49F7A0_ResetOrdersUnitsDAT =			0x0049F7A0;
	const u32 Func_Sub_4A1E50_Orders_AIPatrol =				0x004A1E50;
	const u32 Func_ToggleUnitPath =							0x004E42A0;
	const u32 Func_Sub_4E5F30_GetRightClickActionOrder =	0x004E5F30;
	const u32 Func_CreateUnitSelection =					0x004E6180;
	const u32 Func_DestroyUnitSelection =					0x004E6290;
	const u32 Func_Sub_4EBE10_RefreshSprite =				0x004EBE10;
	const u32 Func_Sub_4F3B70_DestroyPowerupImageOverlay =	0x004F3B70;

	//464930
	void disconnectAddOn_Sub464930(CUnit* unit) {

		CUnit* addon_unit;
		CUnit** offset_006D11FC = (CUnit**)0x006D11FC;
		CUnit* offset_006D11FC_backup;

		__asm {
			PUSHAD
			MOV EDI, unit
			MOV ESI, [edi+0x000000C0]
			CALL Func_Sub_47CB90_NameTooLongToBePutHere
			POPAD
		}

		addon_unit = unit->building.addon;
		unit->building.addon = NULL;
		scbw::refreshConsole();

		__asm {
			PUSHAD
			MOV EAX, addon_unit
			CALL Func_PlayBuildingLiftoffSound	//that thing was too complicated to be extracted T_T
			POPAD
		}

		offset_006D11FC_backup = *offset_006D11FC;
		*offset_006D11FC = unit->building.addon;

		if(unit->building.addon->sprite->images.head != NULL) {

			CImage* current_image = unit->building.addon->sprite->images.head;

			do {

				current_image->playIscriptAnim(IscriptAnimation::LiftOff);
				current_image = current_image->link.next;

			}while (current_image != NULL);

		}

		*offset_006D11FC = offset_006D11FC_backup;

	} //void disconnectAddOn_Sub464930(CUnit* unit)

	//49E590
	void removeUnitRefsFromTarget(CUnit* unit, CUnit* target) {

		if(unit == target->currentBuildUnit)
			target->currentBuildUnit = NULL;

		if(unit == target->orderTarget.unit)
			target->orderTarget.unit = NULL;

		if(unit == target->moveTarget.unit)
			target->moveTarget.unit = NULL;

		if(unit == target->autoTargetUnit)
			target->autoTargetUnit = NULL;

		if(unit == target->connectedUnit)
			target->connectedUnit = NULL;

		if(unit == target->irradiatedBy)
			target->irradiatedBy = NULL;

		if(units_dat::BaseProperty[target->id] & UnitProperty::Worker) {

			if(unit == target->worker.targetResource.unit)
				target->worker.targetResource.unit = NULL;

			if(target->worker.isCarryingSomething) {

				if(unit == target->worker.harvestTarget) {

					target->worker.isCarryingSomething = false;
					target->worker.harvestTarget = NULL;

				}

			}

		}else
		if( (target->status & UnitStatus::GroundedBuilding) && (target->building.addon == unit) )
			target->building.addon = NULL;

		
		if( (units_dat::GroupFlags[target->id].isFactory) && //equivalent condition to a call to "StarCraft.exe+7B2E0 unitIsFactoryUnit" internal function
			(unit == target->rally.unit) ) {

			target->rally.unit = NULL;
			target->rally.pt.x = unit->sprite->position.x;
			target->rally.pt.y = unit->sprite->position.y;

		}

		if(target->subunit != NULL) {

			if(units_dat::BaseProperty[target->subunit->id] & UnitProperty::Subunit)
				removeUnitRefsFromTarget(unit,target); //the snake is biting his tail?

		}

		if(target->orderQueueHead != NULL) {

			COrder* current_order = target->orderQueueHead;

			while(current_order != NULL) {

				//instruction "mov [ebp-08], ecx (==current_order->target)" is lost there
				//I hope it wasn't important...at least it's not used by removeOrderFromUnitQueue()

				if(unit == current_order->target.unit) {
					/*removeOrderFromUnitQueue(target)*/;
				}

			}

		}

	} //void RemoveUnitRefsFromTarget(CUnit* unit, CUnit* target)




	//49EFA0
	void readUnitsArray_Sub49EFA0(CUnit* unit, u8 playerId_param, u32 unknown_param) {

		if(playerId_param != unit->playerId) {

			bool bIsUnitReallyCompleted;
			bool bWasUnitSelected;
			u8 savedSelectionIndex;

			__asm {

				PUSHAD

				MOV ECX, unit
				CALL Func_Sub_4A1E50_Orders_AIPatrol

				POPAD

			}

			if(unit->isRemorphingBuilding()) {

				bIsUnitReallyCompleted = false;

				//forcefully enabling the flag
				unit->status |= UnitStatus::Completed;

			}
			else
				bIsUnitReallyCompleted = true;

			__asm {

				PUSHAD

				MOV EDI, unit

				PUSH -0x01
				MOV EAX, unit
				CALL Func_IncrementUnitScores

				TEST BYTE PTR [EDI+0x000000DC], 0x01
				JE skip_to_9EFF5

				PUSH 0x00
				OR ECX, -0x01		//faster than MOV ECX, 0xFFFFFFFF ?
				CALL Func_IncrementUnitScoresEx

				skip_to_9EFF5:
				POPAD

			}

			if(unit->sprite->flags & CSprite_Flags::Selected) {

				bWasUnitSelected = true;
				savedSelectionIndex = unit->sprite->selectionIndex;

				__asm {
					PUSHAD
					MOV EAX, unit
					CALL Func_DestroyUnitSelection
					POPAD
				}

			}
			else {
				bWasUnitSelected = false;
				savedSelectionIndex = 0;
			}

			//from here, connecting the previous and next units of the player link
			//to each other, disconnecting the current unit from the chain

			if(unit->player_link.prev != NULL)
				unit->player_link.prev->player_link.next = unit->player_link.next;

			if(unit->player_link.next != NULL)
				unit->player_link.next->player_link.prev = unit->player_link.prev;

			//Here, disconnecting the unit from the list based on
			//firstPlayerUnit->unit[unit->playerId] if it's the
			//first element

			if(unit == firstPlayerUnit->unit[unit->playerId])
				firstPlayerUnit->unit[unit->playerId] = unit->player_link.next;

			//Finish to disconnect and change the owner

			unit->player_link.prev = NULL;
			unit->player_link.next = NULL;
			unit->playerId = playerId_param;

			if(bWasUnitSelected) {

				__asm {

					PUSHAD

					XOR EAX, EAX
					MOV AL, savedSelectionIndex
					PUSH EAX
					MOV EAX, unit
					CALL Func_CreateUnitSelection

					POPAD

				}

			}

			//for some reason, Starcraft do that again
			unit->player_link.prev = NULL;

			//connect the unit to the list of units of
			//player identified by playerId_param...
			unit->player_link.next = firstPlayerUnit->unit[playerId_param];

			//...and connect the list back to the unit
			if(firstPlayerUnit->unit[playerId_param] != NULL)
				firstPlayerUnit->unit[playerId_param]->player_link.prev = unit;

			firstPlayerUnit->unit[playerId_param] = unit;

			__asm {

				PUSHAD

				MOV EDI, unit

				PUSH 0x01
				MOV EAX, unit
				CALL Func_IncrementUnitScores

				TEST BYTE PTR [EDI+0x000000DC], 0x01
				JE skip_to_9F0AA

				PUSH unknown_param //there's really a case where a 32 bits register is that value, so it's ok like this
				MOV ECX, 0x00000001
				CALL Func_IncrementUnitScoresEx

				skip_to_9F0AA:
				POPAD

			}

			if(!bIsUnitReallyCompleted)
				unit->status &= ~UnitStatus::Completed; //re-disabling the flag

			__asm {
				PUSHAD
				MOV EDI, unit
				CALL Func_Sub_476D30_DoWeaponIscript
				POPAD
			}

			scbw::refreshConsole();

			if(
				!units_dat::GroupFlags[unit->id].isNeutral &&
				units_dat::GroupFlags[unit->id].isBuilding &&
				unit->status & UnitStatus::GroundedBuilding
				)
				*canUpdatePoweredStatus = 1;

			__asm {
				PUSHAD
				MOV EAX, unit
				CALL Func_Sub_463040_AI_PlaceGuard
				POPAD
			}

			if(
				unit->subunit != NULL &&
				units_dat::BaseProperty[unit->subunit->id] & UnitProperty::Subunit
				)
					readUnitsArray_Sub49EFA0(unit->subunit, playerId_param, unknown_param);

			__asm {
				PUSHAD
				MOV ESI, unit
				CALL Func_ApplySpeedUpgradeFromUnitType
				POPAD
			}

			if (
				units_dat::BaseProperty[unit->id] & UnitProperty::Worker &&
				unit->worker.powerup != NULL && 
				unit->worker.powerup->id == UnitId::Powerup_Flag
				) 
			{

				if(
					unit->worker.powerup->playerId == playerId_param ||
					(unit->worker.powerup->playerId != playerId_param &&
					 playerId_param >= 8)
					)

					__asm {
						PUSHAD
						PUSH unit
						CALL Func_Sub_4F3B70_DestroyPowerupImageOverlay
						POPAD
					}

			}

		} //if(playerId_param != unit->playerId) {
	
	} //void readUnitsArray_Sub49EFA0(CUnit* unit, u8 playerId_param, u32 unknown_param)

	//4A1EF0
	void ordersRescuePassive(CUnit* unit) {

		const u32 offset_006BEE6C = 0x006BEE6C;
		const u32 offset_006BEE64 = 0x006BEE64;

		scbw::UnitFinder unit_finder;
		int unit_finder_index = 0;
		int unit_finder_items_count;

		if(unit->mainOrderTimer == 0) {

			unit->mainOrderTimer = 1;

			unit_finder.search(
				(unit->sprite->position.x >= 0x40) ? unit->sprite->position.x - 0x40 : 0,
				(unit->sprite->position.y >= 0x40) ? unit->sprite->position.y - 0x40 : 0,
				unit->sprite->position.x + 0x40,
				unit->sprite->position.y + 0x40
				);

			unit_finder_items_count = unit_finder.getUnitCount();

			if(unit_finder_items_count != 0) {

				bool jump_to_A2105 = false;

				if (playerTable[unit_finder.getUnit(unit_finder_index)->playerId].type != PlayerType::Human) {

					unit_finder_index++;

					while( 
						(unit_finder_index != unit_finder_items_count) && 
						(playerTable[unit_finder.getUnit(unit_finder_index)->playerId].type != PlayerType::Human)
						)
						unit_finder_index++;

					if(unit_finder_index == unit_finder_items_count)
						jump_to_A2105 = true;

				}
				if(!jump_to_A2105) {

					CUnit* unit_found = unit_finder.getUnit(unit_finder_index);
					bool jump_to_A204A = false;
					bool jump_to_A2052;
					bool jump_to_A20B2 = false;

					if( (unit->status & UnitStatus::Completed) ||
						unit->id == UnitId::ZergHive ||
						unit->id == UnitId::ZergLair
						)
						jump_to_A2052 = false;
					else
					if(unit->id != UnitId::ZergHatchery)
						jump_to_A2052 = true;
					else {

						if (unit->isRemorphingBuilding())
							jump_to_A2052 = false;
						else
							jump_to_A2052 = true;

					}

					//A1FA4:
					if(!jump_to_A2052) {

						if(!(unit->status & UnitStatus::GroundedBuilding) ||
							!(units_dat::BaseProperty[unit->id] & UnitStatus::CanNotReceiveOrders))
							jump_to_A2052 = true;
						else
						if(firstPlayerUnit->unit[unit->playerId] == NULL)
							jump_to_A20B2 = true;

					}

					if(!jump_to_A2052 && !jump_to_A20B2) {

						CUnit* localFirstPlayerUnit = firstPlayerUnit->unit[unit->playerId];

						do {

							//A1FD4:

							if(localFirstPlayerUnit->sprite != NULL &&
								localFirstPlayerUnit->mainOrderId != 0)
							{

								//readUnitsArray_Sub49EFA0(firstPlayerUnit->unit[unit->playerId], unit_found->playerId);
								__asm {

									PUSHAD

									PUSH 0x01

									MOV ECX, localFirstPlayerUnit

									XOR EDX, EDX
									MOV EAX, unit_found
									MOV DL, [EAX+0x4C]
									PUSH EDX

									CALL Func_Sub_49EFA0_ReadUnitsArray

									POPAD

								}

								localFirstPlayerUnit->userActionFlags |= 1;

								if(localFirstPlayerUnit->status & UnitStatus::InBuilding)
									localFirstPlayerUnit->order(OrderId::BunkerGuard, 0, 0, NULL, UnitId::None, true);
								else
									localFirstPlayerUnit->order(units_dat::HumanIdleOrder[localFirstPlayerUnit->id] , 0, 0, NULL, UnitId::None, true);

								prepareForNextOrder(localFirstPlayerUnit);

							}

							//A204A

							localFirstPlayerUnit = localFirstPlayerUnit->player_link.next;

							if(localFirstPlayerUnit == NULL)
								jump_to_A20B2 = true;

						}while (localFirstPlayerUnit != NULL);

					} //if(!jump_to_A2052 && !jump_to_A20B2) {

					if(!jump_to_A20B2) {

						//A2052:

						__asm {

							PUSHAD

							PUSH 0x01

							MOV ECX, unit

							MOV EBX, unit_found
							XOR EAX, EAX
							MOV AL, [EBX+0x4C]
							PUSH EAX

							CALL Func_Sub_49EFA0_ReadUnitsArray 

							POPAD

						}

						unit->userActionFlags |= 1;

						if(unit->status & UnitStatus::InBuilding)
							unit->order(OrderId::BunkerGuard, 0, 0, NULL, UnitId::None, true);
						else
							unit->order(units_dat::HumanIdleOrder[unit->id] , 0, 0, NULL, UnitId::None, true);

						prepareForNextOrder(unit);

					}

					//A20B2:

					if(!scbw::isInReplay() && unit->playerId != *LOCAL_NATION_ID) {
						unit->sprite->selectionTimer = 45;
						scbw::playSound(playerTable[*LOCAL_NATION_ID].race + SoundId::Misc_ZRescue_wav, unit);
					}

					scbw::refreshConsole();

				} //if(!jump_to_A2105)

			} //if (unit_finder_items_count != 0)

			//A2105
			__asm {
				PUSHAD								/*Here's my theory:*/
				MOV EAX,[offset_006BEE6C]			/*get an array size (which is the 1st real element stored in that array)*/
				MOV EDX,[EAX*4+offset_006BEE6C]		/*get (pointer to) last element of array*/
				DEC EAX								/*decrease the local copy of size by 1*/
				MOV [offset_006BEE6C],EAX			/*set the array size to the decreased size*/
				MOV [offset_006BEE64],EDX			/*put the former last element of array in another place*/
				POPAD
			}

		} //if(unit->mainOrderTimer == 0)

	}
	//4E5D60
	void changeUnitButtonSet(CUnit *unit, u16 buttonSetId) {

	if( (unit->status & UnitStatus::DoodadStatesThing) || //original is "MOV EDX,unit->status";"test DH, 04";jne 
		unit->lockdownTimer != 0 ||
		unit->stasisTimer != 0 ||
		unit->maelstromTimer != 0) {

			//original is "test byte ptr[ edx*4 + Starcraft.exe+264080 ] != 01"
			if ( units_dat::BaseProperty[unit->id] & UnitProperty::Building )
				unit->currentButtonSet = buttonSetId;
			else
			if(buttonSetId == UnitId::None)
				unit->currentButtonSet = buttonSetId;

	}
	else
		unit->currentButtonSet = buttonSetId;

}



	//4E6340
	void hideAndDisableUnit(CUnit *unit) {

		if( !(unit->sprite->flags & CSprite_Flags::Hidden) ) {

			if(*firstVisibleUnit != NULL) {

				CUnit* current_unit = firstVisibleUnit[0];

				removeUnitRefsFromTarget(unit, current_unit); //49E590

				while(current_unit->link.next != NULL) {

					current_unit = current_unit->link.next;

					removeUnitRefsFromTarget(unit, current_unit); //49E590

				}

			} //if(*firstVisibleUnit != NULL)

			if(unit->sprite->flags & CSprite_Flags::Hidden) {

				BinDlg** dialog_structure;

				dialog_structure = (BinDlg**)0x0068AC98;

				if( (*dialog_structure != NULL) && ((CUnit*)((*dialog_structure)->user) == unit) ) {

						(*dialog_structure)->user = NULL;
						(*dialog_structure)->graphic = 0xFFFF;

						__asm {
							PUSHAD
							MOV ESI, dialog_structure
							MOV ESI, [ESI]
							CALL Func_HideDialog
							POPAD
						}
				}

				__asm {
					PUSHAD

					MOV ECX, unit
					CALL Func_ClearUnitTarget

					CALL Func_Sub_49A7F0_CompareUnitRank

					MOV ESI, unit
					CALL Func_SortUnit

					POPAD

				}

				if(unit->status & UnitStatus::GroundedBuilding) {

					__asm {

						PUSHAD

						MOV EDI, unit
						MOV EAX, [EDI+0x0C]				//EAX = unit->sprite
						XOR EDX, EDX					//EDX = NULL
						MOV DX, [EAX+0x16]				//DX = unit->sprite->position.y
						MOVSX EAX, WORD PTR [EAX+0x14]	//EAX = 0xFFFF0000 + unit->sprite->position.x
						PUSH EDX						//use 0x00000000 + unit->sprite->position.y as arg
						PUSH EAX						//use 0xFFFF0000 + unit->sprite->position.x as arg
						MOV EAX, EDI					//EAX = unit

						CALL Func_Sub_469EC0_SortLeftRight

						POPAD

					}

				}

				if(unit->status & UnitStatus::InAir) {

					__asm {
						PUSHAD
						MOV EAX, unit
						CALL Func_RemoveRepulseTile
						POPAD
					}

				}

				__asm {
					PUSHAD
					MOV ESI, unit
					CALL Func_ToggleUnitPath
					POPAD
				}

				__asm {

					PUSHAD

					MOV EDI, unit
					MOV ECX,[EDI+0x0C]						//ECX = unit->sprite
					MOV AL,[EDI+0x00000105]					//AL = unit->pathingFlags
					MOV [EDI+0x00000097], 0x00				//unit->movementState = 0x00 (was BL and BL == 0x00 )
					CMP BYTE PTR [ECX+0x0D], 0x0C			//cmp(unit->sprite->elevationLevel,12)
					SETB DL
					XOR DL,AL
					AND DL,01
					XOR AL,DL
					MOV [EDI+0x00000105], AL				//unit->pathingFlags = AL
					MOV EAX,EDI								//EAX = unit
					CALL Func_Sub_49DEA0_AirTrainingProc	//0049DEA0 sub_49DEA0 under airTrainingProc

					POPAD

				}

				if( *firstHiddenUnit != NULL) {

					CUnit** unknownUnitStorage = (CUnit**)0x00628428;

					if(*firstHiddenUnit == *unknownUnitStorage)
						*unknownUnitStorage = unit;

					unit->link.prev = *firstHiddenUnit;
					unit->link.next = (*firstHiddenUnit)->link.next;

					if((*firstHiddenUnit)->link.next != NULL)
						(*firstHiddenUnit)->link.next->link.prev = unit;

					(*firstHiddenUnit)->link.next = unit;

				}
				else {

					CUnit** unknownUnitStorage = (CUnit**)0x00628428;
					*unknownUnitStorage = unit;
					*firstHiddenUnit = unit;

				}

				__asm {

					PUSHAD

					MOV EAX, unit
					XOR EBX, EBX			//set EBX as NULL as it is normally at this point
					MOV EAX, [EAX+0x0C]		//EAX = unit->sprite
					MOV DL, [EAX+0x0E]		//DL = unit->sprite->flags
					OR DL, 0x20				//set CSprite_Flags::Hidden on DL
					PUSH EBX				//NULL pushed as arg
					MOV EBX, EAX			//EBX = unit->sprite
					MOV [EAX+0x0E], DL		//unit->sprite->flags = DL
					CALL Func_Sub_497480_GetSpriteUnderlay

					POPAD

				}

				if(unit->subunit != NULL) {

					CUnit* currentSubUnit = unit->subunit;

					if (units_dat::BaseProperty[currentSubUnit->id] & UnitProperty::Subunit) {

						__asm {

							PUSHAD

							MOV EDI, currentSubUnit
							MOV EBX, [EDI+0x0C]		//EBX = unit->subunit->sprite
							MOV CL, [EBX+0x0E]		//CL = unit->subunit->sprite->flags
							OR CL, 0x20				//set CSprite_Flags::Hidden on CL
							PUSH 0x00				//push 00 as arg
							MOV [EBX+0x0E], CL		//unit->subunit->sprite->flags = CL
							CALL Func_Sub_497480_GetSpriteUnderlay

							POPAD

						}

					}

				}

			} //if(unit->sprite->flags & CSprite_Flags::Hidden)

		} //if( !(unit->sprite->flags & CSprite_Flags::Hidden) )


	/*
		__asm {

			PUSHAD
			PUSH EDI
			MOV EDI,EAX						//EDI = unit
			MOV EAX,[EDI+0x0C]				//EAX = unit->sprite
			TEST BYTE PTR [EAX+0E],20		//if(unit->sprite->flags != CSprite_Flags::Hidden)
			JNE STARCRAFT.EXE+E6486			//jump to last "pop edi"

			PUSH EBX
			PUSH ESI
			MOV ESI,[STARCRAFT.EXE+228430]	//ESI = firstVisibleUnit
			XOR EBX,EBX						//EBX = NULL
			CMP ESI,EBX						//if (ESI == NULL)
			JE STARCRAFT.EXE+E636F			//jump
			MOV EDI,EDI						//unit = unit

			//StarCraft.exe+E6360
			PUSH EDI						//push unit as parameter
			MOV ECX,ESI						//ECX = firstVisibleUnit[0]
			CALL STARCRAFT.EXE+9E590		//0049E590 sub_49E590 nicknamed RemoveUnitRefsFromTarget()

			MOV ESI,[ESI+04]				//ESI = firstVisibleUnit->link.next
			CMP ESI,EBX						//if(ESI != NULL)
			JNE STARCRAFT.EXE+E6360			//loop

			//StarCraft.exe+E636F 
			MOV ECX,[EDI+0C]				//ECX = unit->sprite
			TEST BYTE PTR [ECX+0E],20		//if(unit->sprite->flags == CSprite_Flags::Hidden)
			JE STARCRAFT.EXE+E6395			//jump

			MOV ESI,[STARCRAFT.EXE+28AC98]	//ESI = some constant at 0068AC98
			CMP ESI,EBX						//if null
			JE STARCRAFT.EXE+E6395			//jump

			CMP EDI,[ESI+26]				//if unit != (const->0x26) (constant holding units?)
			JNE STARCRAFT.EXE+E6395			//jump

			MOV [ESI+26],EBX				//[ESI+26] = NULL
			MOV WORD PTR [ESI+24],FFFF		//[ESI+24] = FFFF
			CALL STARCRAFT.EXE+18700		//00418700 HideDialog

			//StarCraft.exe+E6395
			MOV ECX,EDI						//ECX = unit
			CALL STARCRAFT.EXE+8AAC0		//0048AAC0 clearUnitTarget

			CALL STARCRAFT.EXE+9A7F0		//0049A7F0 sub_49A7F0 under compareUnitRank

			MOV EAX,EDI						//EAX = unit
			CALL STARCRAFT.EXE+9F7A0		//0049F7A0 sub_49F7A0 under resetOrdersUnitsDAT

			MOV ESI,EDI						//ESI = unit
			CALL STARCRAFT.EXE+6A300		//0046A300 sortUnit

			TEST BYTE PTR [EDI+000000DC],02	//if(unit->status & UnitStatus::GroundedBuilding)
			JE STARCRAFT.EXE+E63CE			//jump

			MOV EAX,[EDI+0C]				//EAX = unit->sprite
			XOR EDX,EDX						//EDX = NULL
			MOV DX,[EAX+16]					//DX = unit->sprite->position.y
			MOVSX EAX,WORD PTR [EAX+14]		//EAX = 0xFFFF0000 + unit->sprite->position.x
			PUSH EDX						//use 0x00000000 + unit->sprite->position.y as arg
			PUSH EAX						//use 0xFFFF0000 + unit->sprite->position.x as arg
			MOV EAX,EDI						//EAX = unit
			CALL STARCRAFT.EXE+69EC0		//00469EC0  sub_469EC0 under sortLeftRight

			//StarCraft.exe+E63CE
			TEST BYTE PTR [EDI+000000DC],04	//if(unit->status & UnitStatus::InAir)
			JE STARCRAFT.EXE+E63DE			//jmp

			MOV EAX,EDI						//EAX = unit
			CALL STARCRAFT.EXE+533D0		//004533D0 removeRepulseTile

			//StarCraft.exe+E63DE
			MOV ESI,EDI						//ESI = unit
			CALL STARCRAFT.EXE+E42A0		//004E42A0  toggleUnitPath

			MOV ECX,[EDI+0C]				//ECX = unit->sprite
			MOV AL,[EDI+00000105]			//AL = unit->pathingFlags
			MOV [EDI+00000097],BL			//unit->movementState = BL (BL == NULL ? )
			CMP BYTE PTR [ECX+0D],0C		//cmp(unit->sprite->elevationLevel,12)
			SETB DL							//set DL to 1 if below, else set it to 0
			XOR DL,AL						//DL = (0 or 1) | (unit->pathingFlags usually 0 or 1)
			AND DL,01						//0 if DL was 0, 1 if DL was 1 ?
			XOR AL,DL						//AL = (unit->pathingFlags usually 0 or 1) | (0 or 1) |
			MOV [EDI+00000105],AL			//unit->pathingFlags = AL
			MOV EAX,EDI						//EAX = unit
			CALL STARCRAFT.EXE+9DEA0		//0049DEA0 sub_49DEA0 under airTrainingProc

			MOV EAX,[STARCRAFT.EXE+2283EC]	//EAX = *firstHiddenUnit
			CMP EAX,EBX						//if EAX == NULL
			JE STARCRAFT.EXE+E643C			//jump

			CMP [STARCRAFT.EXE+228428],EAX	//cmp some const with *firstHiddenUnit
			JNE STARCRAFT.EXE+E6426			//if not equal jump

			MOV [STARCRAFT.EXE+228428],EDI	//mov unit into some const

			//StarCraft.exe+E6426
			MOV [EDI],EAX					//unit->link.prev = firstHiddenUnit
			MOV ECX,[EAX+04]				//ECX = firstHiddenUnit->link.next
			MOV [EDI+04],ECX				//unit->link.next = firstHiddenUnit->link.next
			MOV ECX,[EAX+04]				//ECX = firstHiddenUnit->link.next
			CMP ECX,EBX						//if firstHiddenUnit->link.next == NULL
			JE STARCRAFT.EXE+E6437			//jump

			MOV [ECX],EDI					//firstHiddenUnit->link.next->link.prev = unit

			//StarCraft.exe+E6437
			MOV [EAX+04],EDI				//firstHiddenUnit->link.next = unit
			JMP STARCRAFT.EXE+E6448			//always jump

			//StarCraft.exe+E643C
			MOV [STARCRAFT.EXE+228428],EDI	//mov unit into some const
			MOV [STARCRAFT.EXE+2283EC],EDI  //mov unit into firstHiddenUnit

			//StarCraft.exe+E6448
			MOV EAX,[EDI+0C]				//EAX = unit->sprite
			MOV DL,[EAX+0E]					//DL = unit->sprite->flags
			OR DL,20						//set CSprite_Flags::Hidden on DL
			PUSH EBX						//NULL pushed as arg
			MOV EBX,EAX						//EBX = unit->sprite
			MOV [EAX+0E],DL					//unit->sprite->flags = DL
			CALL STARCRAFT.EXE+97480		//00497480 sub_497480 under getSpriteUnderlay

			MOV EDI,[EDI+70]				//EDI = unit->subunit
			TEST EDI,EDI					//if EDI == NULL
			JE STARCRAFT.EXE+E6484			//jump

			MOVZX EDX,WORD PTR [EDI+64]		//EDX = 0x00000000 + unit->subunit->id
			TEST BYTE PTR [EDX*4+STARCRAFT.EXE+264080],10	//if units_dat::BaseProperty[unit->subunit->id] & Subunit
			JE STARCRAFT.EXE+E6484							//jump to memory release

			MOV EBX,[EDI+0C]				//EBX = unit->subunit->sprite
			MOV CL,[EBX+0E]					//CL = unit->subunit->sprite->flags
			OR CL,20						//set CSprite_Flags::Hidden on CL
			PUSH 00							//push 00 as arg
			MOV [EBX+0E],CL					//unit->subunit->sprite->flags = CL
			CALL STARCRAFT.EXE+97480		//00497480 sub_497480 under getSpriteUnderlay

			//StarCraft.exe+E6484
			POP ESI
			POP EBX
			POP EDI
			RET 
			POPAD

		}
	*/
	} //void hideAndDisableUnit(CUnit *unit)


	//4E6490
	void showAndEnableUnit(CUnit *unit) {

		if(unit->sprite->flags & CSprite_Flags::Hidden) {

			unit->sprite->flags -= CSprite_Flags::Hidden;

			if(unit->subunit != NULL) {

				if(units_dat::BaseProperty[unit->subunit->id] & UnitProperty::Subunit)
					unit->subunit->sprite->flags -= CSprite_Flags::Hidden;

			}

			__asm {
				PUSHAD
				PUSH unit
				CALL Func_Sub_4E5F30_GetRightClickActionOrder
				POPAD
			}

			__asm {
				PUSHAD
				MOV EDI, unit
				MOV ESI, unit
				CALL Func_Sub_4E5F30_GetRightClickActionOrder
				CALL Func_UpdateUnitOrderFinder
				POPAD
			}

			if(unit->status & UnitStatus::GroundedBuilding) {

				__asm {
					PUSHAD
					MOV EDI, unit
					MOV EAX, [EDI+0x0C]					//EAX = unit->sprite
					XOR ECX, ECX						//ECX = NULL
					MOV CX, [EAX+0x16]					//CX = unit->sprite->position.y
					XOR EDX, EDX						//EDX = NULL
					MOV DX, [EAX+0x14]					//DX = unit->sprite->position.x
					MOV EAX, EDI						//EAX = unit
					PUSH ECX							//PUSH unit->sprite->position.y as arg
					PUSH EDX							//PUSH unit->sprite->position.x as arg	
					CALL Func_Sub_469F60_SortLeftRight
					POPAD
				}

			}

			__asm {
				PUSHAD
				MOV EAX, unit
				CALL Func_Sub_42D9A0_IsVisible
				POPAD
			}

			if(unit->status & UnitStatus::InAir) {

				__asm {
					PUSHAD
					MOV ESI, unit
					CALL Func_SetRepulseAngle
					POPAD
				}

			}

			__asm {
				PUSHAD
				MOV ESI, unit
				CALL Func_ToggleUnitPath
				POPAD
			}

			unit->movementState = 0;

			__asm {
				PUSHAD
				MOV EDI, unit
				MOV EAX, [EDI+0x0C]			//EAX = unit->sprite
				MOV CL, [EAX+0x0D]			//CL = unit->sprite->elevationLevel
				MOV AL, [EDI+0x00000105]	//AL = unit->pathingFlags
				CMP CL, 0x0C				//CMP(unit->sprite->elevationLevel, 12)
				SETB CL
				XOR CL, AL
				AND CL, 0x01
				MOV DL, AL
				XOR DL, CL
				MOV [EDI+0x00000105], DL	//unit->pathingFlags = DL
				POPAD
			}

			if(unit->subunit != NULL) {

				CUnit* subunit = unit->subunit;

				if(units_dat::BaseProperty[unit->subunit->id] & UnitProperty::Subunit) {

					__asm {

						PUSHAD

						MOV ESI, subunit
						CALL Func_ToggleUnitPath

						MOV EAX, [ESI+0x0C]					//EAX = subunit->sprite
						MOV BL, [ESI+0x00000105]			//AL = subunit->pathingFlags
						MOV BYTE PTR [ESI+0x00000097], 00	//subunit->movementState = 0
						CMP BYTE PTR [EAX+0x0D], 0x0C		//CMP(subunit->sprite->elevationLevel, 12)
						SETB CL
						XOR CL, BL
						AND CL, 0x01
						MOV AL, BL
						XOR AL, CL
						MOV [ESI+0x00000105], AL	//subunit->pathingFlags = AL

						POPAD

					}



				}

			}

			__asm {

				PUSHAD

				MOV EAX, unit
				CALL Func_Sub_49DE50_AirTrainingProc

				POPAD

			}

			if( *firstVisibleUnit == NULL) {

				CUnit** unknown_memory_area = (CUnit**)0x0059CC9C;

				*unknown_memory_area = unit;
				*firstVisibleUnit = unit;

			}
			else {

				CUnit** unknown_memory_area = (CUnit**)0x0059CC9C;

				if(*firstVisibleUnit == *unknown_memory_area)
					*unknown_memory_area = unit;

				unit->link.prev = *firstVisibleUnit;
				unit->link.next = (*firstVisibleUnit)->link.next;

				if((*firstVisibleUnit)->link.next != NULL)
					(*firstVisibleUnit)->link.next->link.prev = unit;

				(*firstVisibleUnit)->link.next = unit;


			}

		} //if(unit->sprite->flags & CSprite_Flags::Hidden)

	} //void showAndEnableUnit(CUnit *unit)
	//4EB290
	void setNextWaypoint_Sub4EB290(CUnit* unit) {

		if(unit->pathingFlags & 2)
			unit->pathingFlags |= 4;

		/* START sub_4957A0 START */

		if(!(unit->movementFlags & 4)) {

			u8 movementFlagsBackup = unit->movementFlags;

			unit->moveTarget.pt.x = unit->position.x;
			unit->moveTarget.pt.y = unit->position.y;
			unit->moveTarget.unit = NULL;
			unit->nextMovementWaypoint = unit->moveTarget.pt;

			unit->movementFlags &= -0x71;	//binary: 10001111

			if((unit->movementFlags & 2) && (unit->flingyMovementType == 0)) {

				u32 flingyHaltDistance;
				int xVarComputing;
				int yVarComputing;

				__asm {
					PUSHAD
					MOV ECX, unit
					CALL Func_GetFlingyHaltDistance
					MOV flingyHaltDistance, EAX
					POPAD
				}

				xVarComputing = angleDistance[unit->velocityDirection1].x;
				xVarComputing *= flingyHaltDistance;
				xVarComputing /= 256;
				xVarComputing += unit->halt.x;
				xVarComputing /= 256;
				unit->moveTarget.pt.x = xVarComputing;

				yVarComputing = angleDistance[unit->velocityDirection1].y;
				yVarComputing *= flingyHaltDistance;
				yVarComputing /= 256;
				yVarComputing += unit->halt.y;
				yVarComputing /= 256;
				unit->moveTarget.pt.y = yVarComputing;

				unit->nextMovementWaypoint = unit->moveTarget.pt;

				if(
					(unit->moveTarget.pt.x != unit->sprite->position.x) || 
					(unit->moveTarget.pt.y != unit->sprite->position.y)
				)
					unit->movementFlags = (movementFlagsBackup | 4);

			}

		} 

		/*** END sub_4957A0 END ***/

		__asm {

			PUSHAD

			PUSH EDI			//allocate stack memory for EBP-4
			MOV ESI, unit

			MOV EDI, [ESI+0x10]	//unit->moveTarget
			MOV AX, [ESI+0x64]	//unit->id
			LEA EDX, [EBP-0x04]	//EDX become a pointer on the stack
			MOV [EBP-0x04], EDI	//a copy of unit->moveTarget is the target of [EDX]
			CALL Func_FixTargetLocation

			MOV EAX, [EBP-0x04]	//EAX = modified unit->moveTarget
			CMP EAX, EDI		//compare the modified and original unit->moveTarget
			POP EDI				//free stack memory of EBP-4
			JE jump_to_end

			MOV [ESI+0x10], EAX	//unit->moveTarget = modified unit->moveTarget
			MOV [ESI+0x18], EAX	//unit->nextMovementWaypoint = modified unit->moveTarget.pt

			jump_to_end:

			POPAD
		}
		//Note: it's big because extracting "modified unit->moveTarget" would take too
		//much time, if it's even possible.

		unit->recentOrderTimer = 15;

	} //setNextWaypoint_Sub4EB290(CUnit* unit)

} //namespace helpers
