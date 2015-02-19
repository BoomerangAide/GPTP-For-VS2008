#include "detector.h"
#include "../SCBW/scbwdata.h"
#include "../SCBW/enumerations.h"

// V241 for VS2008

namespace hooks {

/// Determines whether this unit can detect cloaked/burrowed units.
/// This affects CUnit::canDetect().
/// This overrides the EXE edit settings for Detectors in FireGraft.
bool unitCanDetectHook(const CUnit *unit) {
  //Default StarCraft behavior
  return units_dat::BaseProperty[unit->id] & UnitProperty::Detector
         && unit->status & UnitStatus::Completed    // Is completed
         && !unit->isFrozen()
         && !unit->isBlind;
}

//Check if the @p unit can see the @p target (assuming target is cloaked).
u32 getCloakedTargetVisibility(const CUnit *unit, const CUnit* target) {
  //Default StarCraft behavior
  if (target->status & UnitStatus::IsHallucination)
    return 0;

  if (unit->canDetect() && unit != target) {
    if (target->sprite->isVisibleTo(unit->playerId)) {
      u32 detectionRange;

      if (unit->status & UnitStatus::GroundedBuilding)
        detectionRange = 224;
      else
        detectionRange = 32 * unit->getSightRange();

      if (unit->getDistanceToTarget(target) <= detectionRange)
        return ((1 << unit->playerId) | playerVision->flags[unit->playerId] | unit->parasiteFlags);
    }
  }

  return 0;
}

} //hooks