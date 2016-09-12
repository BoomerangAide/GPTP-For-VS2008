#include "unit_morph.h"
#include <hook_tools.h>
#include <SCBW/api.h>
#include <cassert>

namespace {

//-------- CMDRECV_UnitMorph --------//

const u32 Func_AddUnitToBuildQueue = 0x00467250;
bool addUnitToBuildQueue(CUnit* unit, u16 unitId) {

	static u32 result;
	static u32 unitId_;

	unitId_ = unitId;

	__asm {
		PUSHAD
		PUSH unitId_
		MOV EDI, unit
		CALL Func_AddUnitToBuildQueue
		MOV result, EAX
		POPAD
	}

	return result != 0;

}

void __stdcall unitMorphWrapper_CMDRECV_UnitMorph(u8 *commandData) {

	const u16 morphUnitId = *((u16*)&commandData[1]);

	*selectionIndexStart = 0;

	while (CUnit* unit = getActivePlayerNextSelection()) {
		if (hooks::unitCanMorphHook(unit, morphUnitId)
				&& unit->mainOrderId != OrderId::Morph1
				&& addUnitToBuildQueue(unit, morphUnitId))
		{
			unit->orderTo(OrderId::Morph1);
		}
	}

	scbw::refreshConsole();

}

//-------- BTNSCOND_CanBuildUnit --------//

s32 __fastcall unitMorphWrapper_BTNSCOND_CanBuildUnit(u16 buildUnitId, s32 playerId, CUnit* unit) {

	if (*clientSelectionCount <= 1
			|| hooks::getUnitMorphEggTypeHook(unit->id) != UnitId::None)
		return unit->canMakeUnit(buildUnitId, playerId);

	return 0;

}

//-------- Orders_Morph1 --------//

const u32 Hook_Orders_Morph1_Check_Success = 0x0045DFCA;
void __declspec(naked) unitMorphWrapper_Orders_Morph1_Check() {

	static CUnit* unit;

	__asm {
		PUSHAD
		MOV EBP, ESP
		MOV unit, ESI
	}

	if (hooks::getUnitMorphEggTypeHook(unit->id) != UnitId::None) {
		__asm {
			POPAD
			JMP Hook_Orders_Morph1_Check_Success
		}
	}
	else {
		__asm {
			POPAD
			POP EDI
			POP ESI
			MOV ESP, EBP
			POP EBP
			RETN
		}
	}
}

const u32 Hook_Orders_Morph1_EggType_Return = 0x0045E048;
void __declspec(naked) unitMorphWrapper_Orders_Morph1_EggType() {

	static CUnit* unit;
	static u32 morphEggType;

	__asm {
		PUSHAD
		MOV EBP, ESP
		MOV unit, ESI
	}

	unit->status &= ~(UnitStatus::Completed);
	morphEggType = hooks::getUnitMorphEggTypeHook(unit->id);
	assert(hooks::isEggUnitHook(morphEggType));

	__asm {
		POPAD
		PUSH morphEggType
		JMP Hook_Orders_Morph1_EggType_Return
	}
}

//-------- hasSuppliesForUnit --------//

Bool32 __stdcall hasSuppliesForUnitWrapper(u8 playerId, u16 unitId, Bool32 canShowErrorMessage) {
	if (hooks::hasSuppliesForUnitHook(playerId, unitId, canShowErrorMessage != 0))
		return 1;
	else
		return 0;
}

//-------- cancelBuild --------//

typedef void (__stdcall *CancelZergBuildingFunc)(CUnit*);
CancelZergBuildingFunc cancelZergBuilding = (CancelZergBuildingFunc) 0x0045DA40;

const u32 Func_ChangeUnitType = 0x0049FED0;
void changeUnitType(CUnit* unit, u16 newUnitId) {

	static u32 newUnitId_ = newUnitId;

	newUnitId_ = newUnitId;

	__asm {
		PUSHAD
		PUSH newUnitId_
		MOV EAX, unit
		CALL Func_ChangeUnitType
		POPAD
	}

}

const u32 Func_ReplaceSpriteImages = 0x00499BB0;
void replaceSpriteImages(CSprite *sprite, u16 imageId, u8 imageDirection) {

	static u32 imageId_;
	static u32 imageDirection_;

	imageId_ = imageId;
	imageDirection_ = imageDirection;

	__asm {
		PUSHAD
		PUSH imageDirection_
		PUSH imageId_
		MOV EAX, sprite
		CALL Func_ReplaceSpriteImages
		POPAD
	}

}

//-------- cancelUnit --------//

void __fastcall cancelUnitWrapper(CUnit* unit) {
	//Default StarCraft behavior
	if (unit->isDead())
		return;

	if (unit->status & UnitStatus::Completed)
		return;

	if (unit->id == UnitId::nydus_canal && unit->building.nydusExit != NULL)
		return;

	//Don't bother if unit is not morphed yet
	if (unit->id == UnitId::mutalisk || unit->id == UnitId::hydralisk)
		return;

	//Don't bother if unit has finished morphing
	if (		unit->id == UnitId::guardian
			||	unit->id == UnitId::devourer
			||	unit->id == UnitId::lurker)
		return;

	if (unit->status & UnitStatus::GroundedBuilding) {

		if (unit->getRace() == RaceId::Zerg) {
			cancelZergBuilding(unit);
			return;
		}

		resources->minerals[unit->playerId] += units_dat::MineralCost[unit->id] * 3 / 4;
		resources->gas[unit->playerId] += units_dat::GasCost[unit->id] * 3 / 4;

	}
	else {

		u16 refundUnitId;

		if (hooks::isEggUnitHook(unit->id))
			refundUnitId = unit->buildQueue[unit->buildQueueSlot % 5];
		else
			refundUnitId = unit->id;

		resources->minerals[unit->playerId] += units_dat::MineralCost[refundUnitId];
		resources->gas[unit->playerId] += units_dat::GasCost[refundUnitId];

	}

	u16 cancelChangeUnitId = hooks::getCancelMorphRevertTypeHook(unit);

	if (cancelChangeUnitId == UnitId::None) {
		if (unit->id == UnitId::nuclear_missile) {
			CUnit* silo = unit->connectedUnit;
			if (silo) {
				silo->building.silo.nuke = NULL;
				silo->mainOrderState = 0;
			}
			scbw::refreshConsole();
		}
		unit->remove();
	}
	else {
		changeUnitType(unit, cancelChangeUnitId);
		unit->remainingBuildTime = 0;
		unit->buildQueue[unit->buildQueueSlot] = UnitId::None;
		replaceSpriteImages(unit->sprite,
			sprites_dat::ImageId[flingy_dat::SpriteID[units_dat::Graphic[unit->previousUnitType]]], 0);

		unit->orderSignal &= ~0x4;
		unit->playIscriptAnim(IscriptAnimation::SpecialState2);
		unit->orderTo(OrderId::ZergBirth);
	}
}

//-------- getRemainingBuildTimePct --------//

s32 getRemainingBuildTimePctHook(CUnit* unit) {
	u16 unitId = unit->id;
	if (hooks::isEggUnitHook(unitId) || unit->isRemorphingBuilding())
		unitId = unit->buildQueue[unit->buildQueueSlot];

	return 100 * (units_dat::TimeCost[unitId] - unit->remainingBuildTime) / units_dat::TimeCost[unitId];
}

//Inject @ 0x004669E0
void __declspec(naked) getRemainingBuildTimePctWrapper() {

	static CUnit* unit;
	static s32 percentage;

	__asm {
		PUSHAD
		MOV unit, ESI
		MOV EBP, ESP
	}

	percentage = getRemainingBuildTimePctHook(unit);

	__asm {
		POPAD
		MOV EAX, percentage
		RETN
	}

}

//-------- orders_zergBirth --------//

//Inject @ 0x0045DE00
const u32 Hook_GetUnitVerticalOffsetOnBirth_Return = 0x0045DE2C;
void __declspec(naked) getUnitVerticalOffsetOnBirthWrapper() {

	static CUnit* unit;
	static s16 yOffset;

	__asm {
		PUSHAD
		MOV unit, EDI
	}

	yOffset = hooks::getUnitVerticalOffsetOnBirth(unit);

	__asm {
		POPAD
		MOVSX EAX, yOffset
		JMP Hook_GetUnitVerticalOffsetOnBirth_Return
	}

}

//Inject @ 0x0045DE57
const u32 Hook_IsRallyableEggUnit_Yes = 0x0045DE6C;
const u32 Hook_IsRallyableEggUnit_No	= 0x0045DE8B;
void __declspec(naked) isRallyableEggUnitWrapper() {

	static CUnit* unit;

	__asm {
		POP ESI
		POP EBX
		PUSHAD
		MOV unit, EDI
	}

	if (hooks::isRallyableEggUnitHook(unit->previousUnitType)) {
		__asm {
			POPAD
			JMP Hook_IsRallyableEggUnit_Yes
		}
	}
	else {
		__asm {
			POPAD
			JMP Hook_IsRallyableEggUnit_No
		}
	}
}

} //unnamed namespace

namespace hooks {

void injectUnitMorphHooks() {
	callPatch(unitMorphWrapper_CMDRECV_UnitMorph,		0x00486B50);	//jmp 004C1990  CMDRECV_UnitMorph
	jmpPatch(unitMorphWrapper_BTNSCOND_CanBuildUnit,	0x00428E60);	//00428E60  BTNSCOND_CanBuildUnit
	jmpPatch(unitMorphWrapper_Orders_Morph1_Check,		0x0045DFB0);	//0045DEA0  orders_Morph1 within	
	jmpPatch(unitMorphWrapper_Orders_Morph1_EggType,	0x0045E019);	//0045DEA0  orders_Morph1 within
	jmpPatch(hasSuppliesForUnitWrapper,					0x0042CF70);	//0042CF70  hasSuppliesForUnit EXACT
	jmpPatch(cancelUnitWrapper,							0x00468280);	//00468280  AI_CancelStructure EXACT
	jmpPatch(getRemainingBuildTimePctWrapper,			0x004669E0);	//004669E0  sub_4669E0 EXACT
	jmpPatch(getUnitVerticalOffsetOnBirthWrapper,		0x0045DE00);	//0045DD60  orders_ZergBirth within
	jmpPatch(isRallyableEggUnitWrapper,					0x0045DE57);	//0045DD60  orders_ZergBirth within
}

} //hooks
