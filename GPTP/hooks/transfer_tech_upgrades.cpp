//Source file for the Transfer Tech & Upgrades hook module.
//This controls how technologies and upgrades are transferred when units are
//passed from one player to another, either by triggers or casting Mind Control.
#include "transfer_tech_upgrades.h"
#include "apply_upgrade_flags.h"
#include <SCBW/api.h>

namespace {

typedef int (__stdcall *SErrSetLastErrorFunc)(int);
SErrSetLastErrorFunc const SErrSetLastError = (SErrSetLastErrorFunc) 0x00410172;

struct TechTransferData {
  u16 unitId;
  u16 relatedTech[5]; //Maximum number of tech (use TechId::None to mark a premature end-of-list)
};

const TechTransferData techTransferData[] = {
  //Terran
  {UnitId::marine, TechId::Stimpacks, TechId::None},
  {UnitId::firebat, TechId::Stimpacks, TechId::None},
  {UnitId::ghost, TechId::Lockdown, TechId::PersonnelCloaking, TechId::None},
  {UnitId::medic, TechId::Healing, TechId::Restoration, TechId::OpticalFlare, TechId::None},
  {UnitId::vulture, TechId::SpiderMines, TechId::None},
  {UnitId::siege_tank, TechId::TankSiegeMode, TechId::None},
  {UnitId::siege_tank_s, TechId::TankSiegeMode, TechId::None},
  {UnitId::wraith, TechId::CloakingField, TechId::None},
  {UnitId::science_vessel, TechId::DefensiveMatrix, TechId::Irradiate, TechId::EMPShockwave, TechId::None},
  {UnitId::battlecruiser, TechId::YamatoGun, TechId::None},

  //Zerg
  {UnitId::queen, TechId::Infestation, TechId::Parasite, TechId::SpawnBroodlings, TechId::Ensnare, TechId::None},
  {UnitId::defiler, TechId::Burrowing, TechId::DarkSwarm, TechId::Plague, TechId::Consume, TechId::None},
  {UnitId::drone, TechId::Burrowing, TechId::None},
  {UnitId::zergling, TechId::Burrowing, TechId::None},
  {UnitId::hydralisk, TechId::Burrowing, TechId::LurkerAspect, TechId::None},
  {UnitId::infested_terran, TechId::Burrowing, TechId::None},
  {UnitId::lurker, TechId::LurkerAspect, TechId::None},

  //Protoss
  {UnitId::high_templar, TechId::ArchonWarp, TechId::PsionicStorm, TechId::Hallucination, TechId::None},
  {UnitId::arbiter, TechId::Recall, TechId::StasisField, TechId::None},
  {UnitId::corsair, TechId::DisruptionWeb, TechId::None},
  {UnitId::dark_templar, TechId::DarkArchonMeld, TechId::None},
  {UnitId::dark_archon, TechId::MindControl, TechId::Feedback, TechId::Maelstrom, TechId::None},
};

struct UpgradeTransferData {
  u16 unitId;
  u8 relatedUpgrades[4]; //Maximum number of tech (use UpgradeId::None to mark a premature end-of-list)
};

const UpgradeTransferData upgradeTransferData[] = {
  //Terran
  {UnitId::marine, UpgradeId::U_238Shells, UpgradeId::None},
  {UnitId::ghost, UpgradeId::OcularImplants, UpgradeId::MoebiusReactor, UpgradeId::None},
  {UnitId::medic, UpgradeId::CaduceusReactor, UpgradeId::None},
  {UnitId::vulture, UpgradeId::IonThrusters, UpgradeId::None},
  {UnitId::goliath, UpgradeId::CharonBooster, UpgradeId::None},
  {UnitId::science_vessel, UpgradeId::TitanReactor, UpgradeId::None},
  {UnitId::wraith, UpgradeId::ApolloReactor, UpgradeId::None},
  {UnitId::battlecruiser, UpgradeId::ColossusReactor, UpgradeId::None},

  //Zerg
  {UnitId::overlord, UpgradeId::VentralSacs, UpgradeId::Antennae, UpgradeId::None},
  {UnitId::zergling, UpgradeId::MetabolicBoost, UpgradeId::AdrenalGlands, UpgradeId::None},
  {UnitId::hydralisk, UpgradeId::MuscularAugments, UpgradeId::GroovedSpines, UpgradeId::None},
  {UnitId::queen, UpgradeId::GameteMeiosis, UpgradeId::None},
  {UnitId::defiler, UpgradeId::MetasynapticNode, UpgradeId::None},
  {UnitId::ultralisk, UpgradeId::AnabolicSynthesis, UpgradeId::ChitinousPlating, UpgradeId::None},

  //Protoss
  {UnitId::zealot, UpgradeId::LegEnhancements, UpgradeId::None},
  {UnitId::dragoon, UpgradeId::SingularityCharge, UpgradeId::None},
  {UnitId::high_templar, UpgradeId::KhaydarinAmulet, UpgradeId::None},
  {UnitId::dark_archon, UpgradeId::ArgusTalisman, UpgradeId::None},
  {UnitId::reaver, UpgradeId::ScarabDamage, UpgradeId::ReaverCapacity, UpgradeId::None},
  {UnitId::shuttle, UpgradeId::GraviticDrive, UpgradeId::None},
  {UnitId::observer, UpgradeId::SensorArray, UpgradeId::GraviticBoosters, UpgradeId::None},
  {UnitId::scout, UpgradeId::ApialSensors, UpgradeId::GraviticThrusters, UpgradeId::None},
  {UnitId::carrier, UpgradeId::CarrierCapacity, UpgradeId::None},
  {UnitId::arbiter, UpgradeId::KhaydarinCore, UpgradeId::None},
  {UnitId::corsair, UpgradeId::ArgusJewel, UpgradeId::None},
};

} //Unnamed namespace

namespace hooks {

//Transfers all tech related to the @p source unit to @p targetPlayerId.
void transferUnitTechToPlayerHook(const CUnit *source, u8 targetPlayerId) {
  //Default StarCraft behavior

  //Stop if the source unit does not exist
  if (!source) {
    SErrSetLastError(87);
    return;
  }

  for (int i = 0; i < ARRAY_SIZE(techTransferData); ++i) {
    const TechTransferData *data = &techTransferData[i];

    if (source->id == data->unitId) {
      for (int techIndex = 0; techIndex < ARRAY_SIZE(data->relatedTech); ++techIndex) {
        u16 techId = data->relatedTech[techIndex];
        if (techId == TechId::None) break;

        if (scbw::hasTechResearched(source->playerId, techId)
            && !scbw::hasTechResearched(targetPlayerId, techId))
          scbw::setTechResearchState(targetPlayerId, techId, true);
      }
    }
  }
}

//Transfers all upgrades related to the @p source unit to @p targetPlayerId.
void transferUnitUpgradesToPlayerHook(const CUnit *source, u8 targetPlayerId) {
  //Default StarCraft behavior

  //Stop if the source unit does not exist
  if (!source) {
    SErrSetLastError(87);
    return;
  }

  for (int i = 0; i < ARRAY_SIZE(upgradeTransferData); ++i) {
    const UpgradeTransferData *data = &upgradeTransferData[i];

    if (source->id == data->unitId) {
      for (int upgIndex = 0; upgIndex < ARRAY_SIZE(data->relatedUpgrades); ++upgIndex) {
        u8 upgradeId = data->relatedUpgrades[upgIndex];
        if (upgradeId == UpgradeId::None) break;

        u8 sourceUpgradeLevel = scbw::getUpgradeLevel(source->playerId, upgradeId);
        if (sourceUpgradeLevel > scbw::getUpgradeLevel(targetPlayerId, upgradeId))
          scbw::setUpgradeLevel(targetPlayerId, upgradeId, sourceUpgradeLevel);
      }
    }
  }
}

//Transfers all upgrade flags related to the @p unit to the unit's owner.
void applyUnitUpgradeFlagsToAllFriendlyUnitsHook(CUnit *unit) {
  //Default StarCraft behavior

  //Stop if the source unit does not exist
  if (!unit) {
    SErrSetLastError(87);
    return;
  }

  for (int i = 0; i < ARRAY_SIZE(upgradeTransferData); ++i) {
    const UpgradeTransferData *data = &upgradeTransferData[i];

    if (unit->id == data->unitId) {
      for (int upgIndex = 0; upgIndex < ARRAY_SIZE(data->relatedUpgrades); ++upgIndex) {
        u8 upgradeId = data->relatedUpgrades[upgIndex];
        if (upgradeId == UpgradeId::None) break;

        if (scbw::getUpgradeLevel(unit->playerId, upgradeId))
          hooks::applyUpgradeFlagsToExistingUnits(unit, upgradeId);
      }
    }
  }
}

} //hooks
