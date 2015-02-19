//The source file for the Consume hook module.
//This controls the effect of Consume.
//To change the target unit conditions for using Consume, see
//hooks/tech_target_check.cpp

#include "consume.h"
#include <SCBW/scbwdata.h>
#include <SCBW/enumerations.h>
#include "tech_target_check.h"
#include <algorithm>

//-------- Helper function declarations. Do NOT modify! --------//
namespace {
void incrementDeathScores(const CUnit *unit, u8 player);
} //Unnamed namespace

//-------- Actual hook functions --------//

namespace hooks {

/// This function is called when a @p target is consumed by the @p caster.
void consumeHitHook(CUnit *target, CUnit* caster) {
  //Default StarCraft behavior

  //Don't proceed if the target does not exist.
  if (!target)
    return;

  //Don't proceed if the target is invincible.
  if (target->status & UnitStatus::Invincible)
    return;

  //Don't proceed if the target cannot be Consumed.
  if (getTechUseErrorMessage(target, caster->playerId, TechId::Consume) != 0)
    return;

  //Destroy the target unit.
  incrementDeathScores(target, caster->playerId);
  target->remove();

  //Add energy to the caster if the target is not a hallucination.
  if (!(target->status & UnitStatus::IsHallucination)) {
    int energy = caster->energy + 12800; //50 energy
    caster->energy = std::min<int>(energy, caster->getMaxEnergy());
  }
}

} //hooks

//-------- Helper function definitions. Do NOT modify! --------//

namespace {

const u32 Func_IncrementDeathScores = 0x00488AF0;
void incrementDeathScores(const CUnit *unit, u8 player) {
  __asm {
    PUSHAD
    MOV EDI, unit
    MOVZX EDX, player
    CALL Func_IncrementDeathScores
    POPAD
  }
}

} //Unnamed namespace
