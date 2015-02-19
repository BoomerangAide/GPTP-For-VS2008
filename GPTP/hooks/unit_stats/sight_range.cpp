#include "sight_range.h"
#include <SCBW/enumerations.h>
#include <SCBW/scbwdata.h>
#include <SCBW/api.h>

namespace hooks {

/// Returns the modified sight range of the unit, measured in matrices.
/// StarCraft passes 1 for isForSpellCasting when using Feedback, Mind Control,
/// and Hallucination (but not when launching Nukes).
/// Note: sight ranges cannot exceed 11, unless extended.
u32 getSightRangeHook(const CUnit *unit, bool isForSpellCasting) {
  //Default StarCraft logic
  using scbw::getUpgradeLevel;

  //Check if the unit is a constructing building (exclude remorphing buildings)
  if (unit->status & UnitStatus::GroundedBuilding
      && !(unit->status & UnitStatus::Completed)
      && !unit->isRemorphingBuilding())
    return 4;

  //Check if the unit is blinded (don't bother if this is for spellcasting)
  if (!isForSpellCasting && unit->isBlind)
    return 2;

  //Sight range upgrades
  switch (unit->id) {
    case UnitId::ghost:
      if (getUpgradeLevel(unit->playerId, UpgradeId::OcularImplants))
        return 11;
      break;
    case UnitId::overlord:
      if (getUpgradeLevel(unit->playerId, UpgradeId::Antennae))
        return 11;
      break;
    case UnitId::observer:
      if (getUpgradeLevel(unit->playerId, UpgradeId::SensorArray))
        return 11;
      break;
    case UnitId::scout:
      if (getUpgradeLevel(unit->playerId, UpgradeId::ApialSensors))
        return 11;
      break;
  }

  //Default
  return units_dat::SightRange[unit->id];
}

} //hooks
