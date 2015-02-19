//Contains hooks that control attack range and seek range (AKA target acquisition range).

#include "weapon_range.h"
#include <SCBW/scbwdata.h>
#include <SCBW/enumerations.h>
#include <SCBW/api.h>

namespace hooks {

/// Returns the modified seek range (AKA target acquisition range) for the unit.
/// Note: Seek ranges are measured in matrices (1 matrix = 32 pixels).
/// This hook affects the behavior of CUnit::getSeekRange().
u8 getSeekRangeHook(const CUnit *unit) {
  //Default StarCraft behavior
  using UnitStatus::Cloaked;
  using UnitStatus::RequiresDetection;
  using scbw::getUpgradeLevel;

  const u16 unitId = unit->id;

  //Cloaked ghosts do not voluntarily attack enemy units
  if ((unitId == UnitId::ghost
       || unitId == UnitId::sarah_kerrigan
       || unitId == UnitId::Hero_AlexeiStukov
       || unitId == UnitId::Hero_SamirDuran
       || unitId == UnitId::Hero_InfestedDuran)
      && unit->status & (Cloaked | RequiresDetection)
      && unit->mainOrderId != OrderId::HoldPosition2)
    return 0;

  u8 bonusAmount = 0;
  switch (unitId) {
    case UnitId::marine:
      if (getUpgradeLevel(unit->playerId, UpgradeId::U_238Shells))
        bonusAmount = 1;
      break;
    case UnitId::hydralisk:
      if (getUpgradeLevel(unit->playerId, UpgradeId::GroovedSpines))
        bonusAmount = 1;
      break;
    case UnitId::dragoon:
      if (getUpgradeLevel(unit->playerId, UpgradeId::SingularityCharge))
        bonusAmount = 2;
      break;
    case UnitId::fenix_dragoon:
      if (scbw::isBroodWarMode())
        bonusAmount = 2;
      break;
    case UnitId::goliath:
    case UnitId::goliath_turret:
      if (getUpgradeLevel(unit->playerId, UpgradeId::CharonBooster))
        bonusAmount = 3;
      break;
    case UnitId::alan_schezar:
    case UnitId::alan_schezar_turret:
      if (scbw::isBroodWarMode())
        bonusAmount = 3;
      break;
  }

  return units_dat::SeekRange[unitId] + bonusAmount;
}

/// Returns the modified max range for the weapon, which is assumed to be
/// attached to the given unit.
/// This hook affects the behavior of CUnit::getMaxWeaponRange().
/// Note: Weapon ranges are measured in pixels.
///
/// @param  weapon    The weapons.dat ID of the weapon.
/// @param  unit      The unit that owns the weapon. Use this to check upgrades.
u32 getMaxWeaponRangeHook(const CUnit *unit, u8 weaponId) {
  //Default StarCraft behavior
  using scbw::getUpgradeLevel;

  u32 bonusAmount = 0;

  //Give bonus range to units inside Bunkers
  if (unit->status & UnitStatus::InBuilding)
    bonusAmount = 64;

  switch (unit->id) {
    case UnitId::marine:
      if (getUpgradeLevel(unit->playerId, UpgradeId::U_238Shells))
        bonusAmount += 32;
      break;
    case UnitId::hydralisk:
      if (getUpgradeLevel(unit->playerId, UpgradeId::GroovedSpines))
        bonusAmount += 32;
      break;
    case UnitId::dragoon:
      if (getUpgradeLevel(unit->playerId, UpgradeId::SingularityCharge))
        bonusAmount += 64;
      break;
    case UnitId::fenix_dragoon:
      if (scbw::isBroodWarMode())
        bonusAmount += 64;
      break;
    case UnitId::goliath:
    case UnitId::goliath_turret:
      if (weaponId == WeaponId::HellfireMissilePack
          && getUpgradeLevel(unit->playerId, UpgradeId::CharonBooster))
        bonusAmount += 96;
      break;
    case UnitId::alan_schezar:
    case UnitId::alan_schezar_turret:
      if (weaponId == WeaponId::HellfireMissilePack_AlanSchezar
          && scbw::isBroodWarMode())
        bonusAmount += 96;
      break;
  }

  return weapons_dat::MaxRange[weaponId] + bonusAmount;
}

} //hooks
