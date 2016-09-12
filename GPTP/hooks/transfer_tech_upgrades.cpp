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

//summon a function passed as parameter, having the same variables layout for both upgrade and tech related functions.
bool researchHelper(u32 researchTechFunc, CUnit* sourceUnit, u32 techId, u32 relativeVariable,u32 destPlayerId) {

	static u32 bPreResult;

	__asm {
		PUSHAD
		PUSH destPlayerId		//[EBP+0x14]
		PUSH relativeVariable	//[EBP+0x10] //this variable has different meaning depending on the caller (boolean or number) 
		PUSH techId				//[EBP+0x0C]
		PUSH sourceUnit			//[EBP+0x08]
		CALL researchTechFunc
		MOV bPreResult, EAX
		POPAD
	}

	return (bPreResult != 0);

} //bool researchHelper(u32 researchTechFunc, CUnit* sourceUnit, u32 techId, u32 relativeVariable, u32 destPlayerId)

;

//Transfers all tech related to the @p source unit to @p targetPlayerId.
//Originally researchAllTechsFromUnit @ 004E2C00
void transferUnitTechToPlayerHook(CUnit* sourceUnit, u8 targetPlayerId, u32 researchTechFunc) {

	const TechTransferData* techDataArrayPosBegin	= &techTransferData[0];								//original was (TechTransferData*) 0x005011CA;
	const TechTransferData* techDataArrayPosEnd		= &techTransferData[ARRAY_SIZE(techTransferData)];	//original was (TechTransferData*) 0x005012DE;
	const int relatedTechArraySize					= 5;

	//Stop if the source unit does not exist
	if (researchTechFunc == NULL || sourceUnit == NULL)
		SErrSetLastError(87);
	else {

		bool bBreakMainLoop = false;
		bool bBreakSubLoop;

		//Browse through TechTransferData structures
		for (TechTransferData* data = (TechTransferData*)techDataArrayPosBegin; !bBreakMainLoop && (data != techDataArrayPosEnd); data++) {

			if (sourceUnit->id == data->unitId) {

				bBreakSubLoop = false;

				//Browse through techs for current unit
				for (int techIndex = 0; !bBreakSubLoop && techIndex < relatedTechArraySize; techIndex++) {

					u16 techId = data->relatedTech[techIndex];

					//forced end of array, stop checking techs, but still check others TechTransferData
					//(in case the unit is represented several times?)
					if (techId == TechId::None)
						bBreakSubLoop = true;
					else {

						Bool8 bIsResearched;

						//check if tech is researched by unit for transfer
						if(techId >= TechId::Restoration)
							bIsResearched = TechBw->isResearched[sourceUnit->playerId][techId - TechId::Restoration];
						else
							bIsResearched = TechSc->isResearched[sourceUnit->playerId][techId];

						//probably research the tech of unit if not already researched by player
						//if return false, stop checking techs and TechTransferData
						if(!researchHelper(researchTechFunc,sourceUnit,techId,bIsResearched,targetPlayerId)) {
							bBreakSubLoop = true;
							bBreakMainLoop = true;			
						}

					}

				}

			} //if (sourceUnit->id == data->unitId)

		} //for (TechTransferData* data = (TechTransferData*)techDataArrayPosBegin; !bBreakMainLoop && (data != techDataArrayPosEnd); data++)

	} //if (researchTechFunc != NULL && sourceUnit != NULL)

} //void transferUnitTechToPlayerHook(CUnit* sourceUnit, u8 targetPlayerId, u32 researchTechFunc)

;

//Transfers all upgrades related to the @p source unit to @p targetPlayerId.
//Originally upgradeAllUpgradesFromUnit @ 004E2B50
void transferUnitUpgradesToPlayerHook(CUnit* sourceUnit, u8 targetPlayerId, u32 researchUpgradesFunc) {

	const UpgradeTransferData* upgradeDataArrayPosBegin	= &upgradeTransferData[0];									//original was (UpgradeTransferData*) 0x005012E2;
	const UpgradeTransferData* upgradeDataArrayPosEnd	= &upgradeTransferData[ARRAY_SIZE(upgradeTransferData)];	//original was (UpgradeTransferData*) 0x005013DC;
	const int relatedUpgradeArraySize					= 4;

	//Stop if the source unit does not exist
	if (researchUpgradesFunc == NULL || sourceUnit == NULL)
		SErrSetLastError(87);	//0x57
	else {

		bool bBreakMainLoop = false;
		bool bBreakSubLoop;

		//Browse through UpgradeTransferData structures
		for (UpgradeTransferData* data = (UpgradeTransferData*)upgradeDataArrayPosBegin; !bBreakMainLoop && (data != upgradeDataArrayPosEnd); data++) {

			if (sourceUnit->id == data->unitId) {

				bBreakSubLoop = false;

				//Browse through upgrades for current unit
				for (int upgradeIndex = 0; !bBreakSubLoop && upgradeIndex < relatedUpgradeArraySize; upgradeIndex++) {

					u16 upgradeId = data->relatedUpgrades[upgradeIndex];

					//forced end of array, stop checking upgrades, but still check others UpgradeTransferData
					//(in case the unit is represented several times?)
					if (upgradeId == UpgradeId::None)
						bBreakSubLoop = true;
					else {

						u8 sourceUpgradeLevel;

						//check level of upgrade of by unit for transfer
						if(upgradeId >= UpgradeId::UnusedUpgrade46)
							sourceUpgradeLevel = UpgradesBw->currentLevel[sourceUnit->playerId][upgradeId - UpgradeId::UnusedUpgrade46];
						else
							sourceUpgradeLevel = UpgradesSc->currentLevel[sourceUnit->playerId][upgradeId];

						//probably increase the upgrade level of player until reaching same point as sourceUnit
						//if return false, stop checking upgrades and UpgradeTransferData
						if(!researchHelper(researchUpgradesFunc,sourceUnit,upgradeId,sourceUpgradeLevel,targetPlayerId)) {
							bBreakSubLoop = true;
							bBreakMainLoop = true;			
						}

					}

				}

			} //if (sourceUnit->id == data->unitId)

		} //for (upgradeTransferData* data = (upgradeTransferData*)upgradeDataArrayPosBegin; !bBreakMainLoop && (data != upgradeDataArrayPosEnd); data++)

	} //if (researchupgradeFunc != NULL && sourceUnit != NULL)

}

;

} //hooks
