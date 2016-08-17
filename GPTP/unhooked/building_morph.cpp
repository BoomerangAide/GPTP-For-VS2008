#include "building_morph.h"
#include "unit_morph.h"
#include <SCBW/enumerations.h>
#include <SCBW/scbwdata.h>

//V241 for VS2008

//-------- Helper function declarations. Do NOT modify! ---------//

namespace {
int getNumberOfUnitType(const CUnit *unit, u16 unitId, bool ignoreIncomplete);
} //unnamed namespace


//-------- Actual hook functions --------//

namespace hooks {

//Checks if @p unitId is a building that can be morphed from another building.
//Note: This hook affects the behavior of CUnit::isRemorphingBuilding().
bool isMorphedBuildingHook(u16 unitId) {
  //Default StarCraft behavior

  if (unitId == UnitId::lair
      || unitId == UnitId::hive
      || unitId == UnitId::greater_spire
      || unitId == UnitId::sunken_colony
      || unitId == UnitId::spore_colony)
    return true;

  return false;
}

//Determines the number of units which have @p unitId and are being built by the
//@p unit. This hook is used by StarCraft's AI for counting units and buildings.
//For example, Greater Spires are counted as Spires, so that the AI would not
//try to rebuild another Spire after morphing one into a Greater Spire.
int getMorphBuildingTypeCountHook(const CUnit *unit, u16 unitId, bool ignoreIncomplete) {
  //Default StarCraft behavior

  int unitCount = getNumberOfUnitType(unit, unitId, ignoreIncomplete);

  switch (unitId) {
    case UnitId::hatchery:
      unitCount += getNumberOfUnitType(unit, UnitId::lair, ignoreIncomplete);
    case UnitId::lair:
      unitCount += getNumberOfUnitType(unit, UnitId::hive, ignoreIncomplete);
      break;

    case UnitId::creep_colony:
      unitCount += getNumberOfUnitType(unit, UnitId::sunken_colony, ignoreIncomplete);
      unitCount += getNumberOfUnitType(unit, UnitId::spore_colony, ignoreIncomplete);
      break;

    case UnitId::spire:
      unitCount += getNumberOfUnitType(unit, UnitId::greater_spire, ignoreIncomplete);
      break;
  }

  return unitCount;
}

} //hooks


//-------- Helper function definitions. Do NOT modify! --------//

namespace {

//Check if @p unit is warping in a Protoss building.
//Identical to function @ 0x004E4C40
bool isWarpingInProtossBuilding(const CUnit *probe) {
  return probe->mainOrderId == OrderId::BuildProtoss1
    && probe->status & UnitStatus::GroundedBuilding
    && probe->orderTarget.unit != NULL
    && !(probe->orderTarget.unit->status & UnitStatus::Completed);
}

//Check if @p building is in the process of constructing an add-on.
//Identical to function @ 0x004E66B0
bool isConstructingAddon(const CUnit *building) {
  return building->secondaryOrderId == OrderId::BuildAddon
    && building->status & UnitStatus::GroundedBuilding
    && building->currentBuildUnit != NULL
    && !(building->currentBuildUnit->status & UnitStatus::Completed);
}

//Return the building or add-on that the @p unit is constructing.
//Identical to function @ 0x00466A30
CUnit* getConstructRepairTarget(const CUnit *unit) {
  if (unit->mainOrderId == OrderId::BuildTerran
      || unit->mainOrderId == OrderId::Repair1
      || unit->mainOrderId == OrderId::ConstructingBuilding
      || isWarpingInProtossBuilding(unit))
    return unit->orderTarget.unit;

  if (unit->secondaryOrderId == OrderId::Train
      || unit->secondaryOrderId == OrderId::TrainFighter
      || isConstructingAddon(unit))
    return unit->currentBuildUnit;

  return NULL;
}

//Identical to function @ 0x00466B70
int getNumberOfUnitTypeInBuildQueue(const CUnit *unit, u16 unitId) {
  if (units_dat::BaseProperty[unit->id] & UnitProperty::Worker) {
    if (getConstructRepairTarget(unit) == NULL
        && unit->buildQueue[unit->buildQueueSlot % 5] == unitId
        && (unit->mainOrderId == OrderId::BuildTerran
            || unit->mainOrderId == OrderId::BuildProtoss1
            || unit->mainOrderId == OrderId::DroneLand
            || unit->mainOrderId == OrderId::DroneBuild
            || unit->mainOrderId == OrderId::DroneStartBuild))
      return 1;
    else
      return 0;
  }

  if (hooks::isEggUnitHook(unit->id)
      || unit->mainOrderId == OrderId::Morph2
      || unit->mainOrderId == OrderId::ZergBuildSelf)
    return (unit->buildQueue[unit->buildQueueSlot % 5] == unitId) ? 1 : 0;

  int unitCount = 0;
  for (int i = 0; i < 5; ++i) {
    if (unit->buildQueue[(unit->buildQueueSlot + i) % 5] == unitId)
      ++unitCount;
  }
  return unitCount;
}

int getNumberOfUnitType(const CUnit *unit, u16 unitId, bool ignoreIncomplete) {
  if (!ignoreIncomplete || unit->status & UnitStatus::Completed) {
    if (unit->id == unitId)
      return 1;

    if (!ignoreIncomplete)
      return getNumberOfUnitTypeInBuildQueue(unit, unitId);
  }

  return 0;
}

} //unnamed namespace
