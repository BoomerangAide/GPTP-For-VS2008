#include "max_energy.h"
#include <SCBW/scbwdata.h>
#include <SCBW/enumerations.h>
#include <SCBW/api.h>

namespace hooks {

/// Replaces the CUnit::getMaxEnergy() function.
/// Return the amount of maximum energy that a unit can have.
/// Note: 1 energy displayed in-game equals 256 energy.
u16 getUnitMaxEnergyHook(const CUnit* const unit) {
  //Default StarCraft behavior
  using scbw::getUpgradeLevel;
  if (units_dat::BaseProperty[unit->id] & UnitProperty::Hero)
    return 64000; //250

  switch (unit->id) {
    case UnitId::science_vessel:
      if (getUpgradeLevel(unit->playerId, UpgradeId::TitanReactor))
        return 64000; //250
      break;
    case UnitId::ghost:
      if (getUpgradeLevel(unit->playerId, UpgradeId::MoebiusReactor))
        return 64000; //250
      break;
    case UnitId::wraith:
      if (getUpgradeLevel(unit->playerId, UpgradeId::ApolloReactor))
        return 64000; //250
      break;
    case UnitId::battlecruiser:
      if (getUpgradeLevel(unit->playerId, UpgradeId::ColossusReactor))
        return 64000; //250
      break;
    case UnitId::queen:
      if (getUpgradeLevel(unit->playerId, UpgradeId::GameteMeiosis))
        return 64000; //250
      break;
    case UnitId::defiler:
      if (getUpgradeLevel(unit->playerId, UpgradeId::MetasynapticNode))
        return 64000; //250
      break;
    case UnitId::high_templar:
      if (getUpgradeLevel(unit->playerId, UpgradeId::KhaydarinAmulet))
        return 64000; //250
      break;
    case UnitId::arbiter:
      if (getUpgradeLevel(unit->playerId, UpgradeId::KhaydarinCore))
        return 64000; //250
      break;
    case UnitId::corsair:
      if (getUpgradeLevel(unit->playerId, UpgradeId::ArgusJewel))
        return 64000; //250
      break;
    case UnitId::medic:
      if (getUpgradeLevel(unit->playerId, UpgradeId::CaduceusReactor))
        return 64000; //250
      break;
    case UnitId::dark_archon:
      if (getUpgradeLevel(unit->playerId, UpgradeId::ArgusTalisman))
        return 64000; //250
      break;
  }

  return 51200; //200
}

} //hooks
