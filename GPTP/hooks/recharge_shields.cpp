#include "recharge_shields.h"
#include "../SCBW/scbwdata.h"
#include "../SCBW/enumerations.h"
#include "../SCBW/api.h"

//-------- Helper function declarations. Do NOT modify! --------//
namespace {
bool orderToMoveToTarget(CUnit *unit, const CUnit *target);
void orderToHoldPosition(CUnit *unit);
void insertFirstOrder(CUnit *unit, u8 orderId);

//Returns:  0 - Unit has not reached destination
//          1 - Unit cannot move
//          2 - Unit has reached destination
int getUnitMovementState(const CUnit *unit);
} //unnamed namespace

//-------- Actual hook functions --------//

//This function is called every frame when a unit recharges shields.
void rechargeShieldsProc(CUnit *target, CUnit *battery) {
  //Default StarCraft behavior

  s32 shieldGain = 1280, energySpent = 640;
  const s32 maxShields = units_dat::MaxShieldPoints[target->id] << 8;

   if (maxShields - target->shields < shieldGain) {
    shieldGain = maxShields - target->shields;
    energySpent = shieldGain / 2;
  }
  if (energySpent > battery->energy) {
    energySpent = battery->energy;
    shieldGain = energySpent * 2;
  }

  s32 shields = target->shields + shieldGain;
  if (shields > maxShields)
    shields = maxShields;
  target->shields = shields;

  if (!scbw::isCheatEnabled(CheatFlags::TheGathering))
    battery->energy -= energySpent;
}

namespace hooks {

/// Decides whether the @p target can recharge shields from the @p battery.
bool unitCanRechargeShieldsHook(const CUnit *target, const CUnit *battery) {
  //Default StarCraft behavior

  //Check target conditions
  if (target->playerId != battery->playerId   //Is not owned by the player
      || !(units_dat::ShieldsEnabled[target->id])  //Does not have shields
      || !(target->status & (UnitStatus::Completed | UnitStatus::IsBuilding)) //Is incomplete?
      || target->status & UnitStatus::GroundedBuilding)                       //Is a building
    return false;

  //Check target race
  if (target->getRace() != RaceId::Protoss)
    return false;

  //Check target shield amount
  if (target->shields >= (units_dat::MaxShieldPoints[target->id] << 8)) //Already has max shields
    return false;

  //Check battery conditions
  if (!(battery->status & UnitStatus::Completed)  //Is being warped in
      || !battery->energy                         //Does not have energy
      || battery->isFrozen())                     //Is frozen
    return false; //Cannot recharge from this battery

  if (target->pAI) { //Separate check for AI-controlled units
    if (target->mainOrderId == OrderId::RechargeShields1 || target->mainOrderId == OrderId::Pickup4)
      return false;
    if (target->orderQueueHead && target->orderQueueHead->orderId == OrderId::RechargeShields1)
      return false;
  }

  return true;
}

//The order process run by a unit when recharging shields
void orderRechargeShieldsHook(CUnit *unit) {
  //Default StarCraft behavior

  CUnit *battery = unit->orderTarget.unit;

  //Skip if the Shield Battery does not exist, has no energy, or is disabled
  if (!battery || battery->energy == 0 || battery->isFrozen()) {
    unit->orderToIdle();
    return;
  }

  switch (unit->mainOrderState) {
    //State 0: Order the unit to move towards the Shield Battery
    case 0:
      if (orderToMoveToTarget(unit, battery))
        unit->mainOrderState = 1;
      break;

    //State 1: Make the unit move until it is close enough and then stop.
    case 1:
      switch (getUnitMovementState(unit)) {
        case 0: //Unit has not reached target yet
          if (unit->getDistanceToTarget(battery) > 128)
            return;
        case 1: //Unit cannot move
          orderToHoldPosition(unit);
          unit->mainOrderState = 2;
          break;

        default:
          unit->orderToIdle();
          return;
      }

    //State 2: Prepare to recharge shields
    case 2:
      battery->setSecondaryOrder(OrderId::ShieldBattery);
      unit->sprite->createOverlay(ImageId::RechargeShields_Small + scbw::getUnitOverlayAdjustment(unit));
      insertFirstOrder(unit, OrderId::Harvest5);  //Stop workers harvesting
      unit->mainOrderState = 3;

    //State 3: Recharge unit shields
    case 3:
      if (!battery->orderTarget.unit)
        battery->orderTarget.unit = unit;
      
      rechargeShieldsProc(unit, battery);

      //Stop recharge condition: Unit is at full shields or Shield Battery has no energy
      if (unit->shields >= units_dat::MaxShieldPoints[unit->id] * 256
          || battery->energy == 0)
      {
        if (battery->orderTarget.unit == unit)
          battery->orderTarget.unit = NULL;
        unit->orderToIdle();
      }
      break;      
  }
}

} //hooks


//-------- Helper function definitions. Do NOT modify! --------//

namespace {

const u32 Helper_OrderToMoveToTarget = 0x004EB980;
bool orderToMoveToTarget(CUnit *unit, const CUnit *target) {

	static Bool32 result;
  
	__asm {
		PUSHAD
		MOV EAX, target
		MOV ECX, unit
		CALL Helper_OrderToMoveToTarget
		MOV result, EAX
		POPAD
	}

	return result != 0;

}

//Identical to function @ 0x00401DC0;
int getUnitMovementState(const CUnit *unit) {
  if (unit->moveTarget.pt != unit->sprite->position)
    return 0;
  else if (!(unit->status & UnitStatus::Unmovable))
    return 1;
  else
    return 2;
}

const u32 Helper_OrderToHoldPosition = 0x004EB5B0;
void orderToHoldPosition(CUnit *unit) {

  __asm {
    PUSHAD
    MOV ESI, unit
    CALL Helper_OrderToHoldPosition
    POPAD
  }
}

const u32 Helper_InsertFirstOrder = 0x004749D0;
void insertFirstOrder(CUnit *unit, u8 orderId) {

  __asm {
    PUSHAD
    MOV AL, orderId
    MOV ECX, unit
    CALL Helper_InsertFirstOrder
    POPAD
  }
}

} //unnamed namespace
