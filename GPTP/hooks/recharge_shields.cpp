#include "recharge_shields.h"
#include "../SCBW/scbwdata.h"
#include "../SCBW/enumerations.h"
#include "../SCBW/api.h"

//-------- Helper function declarations. Do NOT modify! --------//
namespace {
	void insertFirstOrder(CUnit* unit, u8 orderId);			//0x004749D0
	u8 hasOverlay(CUnit* unit);								//0x0047B720
	void makeToHoldPosition(CUnit* unit);					//0x004EB5B0
	bool orderToMoveToTarget(CUnit* unit, CUnit* target);	//0x004EB980
	bool isHangarUnit(CUnit* unit);
} //unnamed namespace

//This function is called every frame when a unit recharges shields.
//Equivalent to 004934B0  sub_4934B0
//Not hooked
void rechargeShieldsProc(CUnit* target, CUnit* battery) {

	const s32 maxShields = units_dat::MaxShieldPoints[target->id] * 256;

	s32 shieldGain = 1280, energySpent = 640;

	if (maxShields - target->shields < shieldGain) {

		shieldGain = maxShields - target->shields;

		if(shieldGain < 0)
			shieldGain++;

		energySpent = shieldGain / 2;

	}

	if (energySpent > battery->energy) {
		energySpent = battery->energy;
		shieldGain = energySpent * 2;
	}

	target->shields = target->shields + shieldGain;

	if (target->shields > maxShields)
		target->shields = maxShields;

	if (!scbw::isCheatEnabled(CheatFlags::TheGathering))
		battery->energy -= energySpent;

}

;

//-------- Actual hook functions --------//

namespace hooks {

/// Decides whether the @p target can recharge shields from the @p battery.
Bool32 unitCanRechargeShieldsHook(CUnit* target, CUnit* battery) {

	Bool32 result;

	//Check target conditions
	if (	target->playerId != battery->playerId ||								//Is not owned by the player
			!(units_dat::ShieldsEnabled[target->id]) ||								//Does not have shields
			!(target->status & UnitStatus::Completed) ||							//Is incomplete?
			!(target->status & UnitStatus::IsBuilding) ||							//Is building (like archon build self)?
			target->status & UnitStatus::GroundedBuilding ||						//Is a building
			target->getRace() != RaceId::Protoss ||									//Check target race
			target->shields >= (units_dat::MaxShieldPoints[target->id] * 256) ||	//Already has max shields
			!(battery->status & UnitStatus::Completed) ||
			battery->energy == 0 ||
			battery->isFrozen() ||
			isHangarUnit(target)
	  )                       
		result = 0;
	else
	if(target->pAI == NULL)
		result = 1;
	else { //Separate check for AI-controlled units
		if (target->mainOrderId == OrderId::RechargeShields1 || target->mainOrderId == OrderId::Pickup4)
			result = 0;
		else
		if (target->orderQueueHead != NULL && target->orderQueueHead->orderId == OrderId::RechargeShields1)
			result = 0;
		else
			result = 1;
	}

	return result;

}

;

//The order process run by a unit when recharging shields
//Identical to orders_RechargeShields1 @ 00493DD0
void orderRechargeShieldsHook(CUnit* unit) {

	const int BATTERY_RANGE = 0x80; //(128)

	CUnit* battery = unit->orderTarget.unit;

	//Skip if the Shield Battery does not exist, has no energy, or is disabled
	//isFrozen code was hardcoded rather than function call in original code
	if (battery == NULL || battery->energy == 0 || battery->isFrozen()) {

		if (unit->orderQueueHead == NULL) {
			unit->userActionFlags |= 1;
			prepareForNextOrder(unit);
		}
		else {
			if (unit->pAI != NULL)
				unit->orderComputerCL(OrderId::ComputerAI);
			else
				unit->orderComputerCL(units_dat::ReturnToIdleOrder[unit->id]);
		}

	}
	else 
	if(unit->mainOrderState <= 3)
	{

		bool bStopThere = false;

		if(unit->mainOrderState == 0) {

			if(orderToMoveToTarget(unit,battery))
				unit->mainOrderState = 1;

			bStopThere = true;

		}
		else
		if(unit->mainOrderState == 1) {

			u32 movableState = unit->getMovableState();

			if(movableState == 0) { //not reached destination
				if(!unit->isTargetWithinMinRange(battery, BATTERY_RANGE))
					bStopThere = true;
			}
			else
			if(movableState == 1) { //unit reached destination
				makeToHoldPosition(unit);
				unit->mainOrderState = 2;
			}
			else { //probably movableState == 2 == unit unmovable
				unit->orderToIdle();
				bStopThere = true;
			}

		}

		if(!bStopThere && unit->mainOrderState == 2) {

			u8 overlaysCounter;

			if(battery->secondaryOrderId != OrderId::ShieldBattery)
				battery->setSecondaryOrder(OrderId::ShieldBattery);

			overlaysCounter = hasOverlay(unit);
			unit->sprite->createOverlay(ImageId::RechargeShields_Small + overlaysCounter,0,0,0);

			//the order is correct, see OrderId.h description
			insertFirstOrder(unit,OrderId::Harvest5);

			unit->mainOrderState = 3;

		}

		if(!bStopThere && unit->mainOrderState == 3) {

			if(battery->orderTarget.unit == NULL)
				battery->orderTarget.unit = unit;

			//do 1 recharge action? (increase unit shield, decrease battery energy)
			rechargeShieldsProc(unit,battery);

			if(
				unit->shields >= units_dat::MaxShieldPoints[unit->id] * 256 ||
				battery->energy == 0
			)
			{

				if(battery->orderTarget.unit == unit)
					battery->orderTarget.unit = NULL;

				unit->orderToIdle();

			}

		} //if(!bStopThere && unit->mainOrderState == 3)

	} //if(unit->mainOrderState <= 3)

} //void orderRechargeShieldsHook(CUnit* unit)

} //hooks


//-------- Helper function definitions. Do NOT modify! --------//

namespace {

const u32 Helper_InsertFirstOrder = 0x004749D0;
void insertFirstOrder(CUnit* unit, u8 orderId) {

	__asm {
		PUSHAD
		MOV AL, orderId
		MOV ECX, unit
		CALL Helper_InsertFirstOrder
		POPAD
	}

}

;

const u32 Func_hasOverlay = 0x0047B720;
/// Return the count of overlays
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

const u32 Func_Sub4934B0 = 0x004934B0;
void function_004934B0(CUnit* unit, CUnit* battery) {

	__asm {
		PUSHAD
		MOV ECX, unit
		MOV EBX, battery
		CALL Func_Sub4934B0
		POPAD
	}

}

;

const u32 Func__moveToTarget = 0x004EB980;
bool orderToMoveToTarget(CUnit* unit, CUnit* target) {

	static Bool32 bPreResult;
  
	__asm {
		PUSHAD
		MOV EAX, target
		MOV ECX, unit
		CALL Func__moveToTarget
		MOV bPreResult, EAX
		POPAD
	}

	return bPreResult != 0;

}

;

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

//Identical to unitIsHangerUnit @ 0x00401450
bool isHangarUnit(CUnit* unit) {
	if(
		unit->id == UnitId::ProtossInterceptor ||
		unit->id == UnitId::ProtossScarab
	)
		return true;
	else
		return false;
}

} //unnamed namespace
