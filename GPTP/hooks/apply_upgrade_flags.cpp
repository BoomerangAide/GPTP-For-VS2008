//Source file for the Apply Upgrade Flags hook module.
//This file is directly responsible for applying movement speed / attack speed
//upgrades to units.
#include "apply_upgrade_flags.h"
#include <SCBW/api.h>

//helper functions def
namespace {

bool upgradeRestrictionProc(CUnit* unit, u8 upgradeId, u32 Func_UpgradeRestrictionProc);

} //unnamed namespace

namespace hooks {

//This hook function is called when creating a new unit.
//Equivalent to ApplySpeedUpgradeFromUnitType @ 00454370
void applyUpgradeFlagsToNewUnitHook(CUnit* unit) {

	Bool8 bSpeedUpgrade = 0, bCooldownUpgrade = 0;

	if(unit->id >= UnitId::TerranVulture && unit->id <= UnitId::ZergLurker) {

		//slightly different from original code, because completely separating Bool8 calculation
		//and update of speed to do everything at once after the checks
		//Note that updateSpeed() is called once even without upgrades

		if(unit->id == UnitId::TerranVulture || unit->id == UnitId::Hero_JimRaynorVulture)
			bSpeedUpgrade = UpgradesSc->currentLevel[unit->playerId][ScUpgrade::IonThrusters];
		else
		if(unit->id == UnitId::ZergOverlord)
			bSpeedUpgrade = UpgradesSc->currentLevel[unit->playerId][ScUpgrade::PneumatizedCarapace];
		else
		if(unit->id == UnitId::ZergZergling) {
			bSpeedUpgrade = UpgradesSc->currentLevel[unit->playerId][ScUpgrade::MetabolicBoost];
			bCooldownUpgrade = UpgradesSc->currentLevel[unit->playerId][ScUpgrade::AdrenalGlands];
		}
		else
		if(unit->id == UnitId::Hero_DevouringOne) {
			bSpeedUpgrade = 1;
			bCooldownUpgrade = 1;
		}
		else
		if(unit->id == UnitId::ZergHydralisk)
			bSpeedUpgrade = UpgradesSc->currentLevel[unit->playerId][ScUpgrade::MuscularAugments];
		else
		if(unit->id == UnitId::ProtossZealot)
			bSpeedUpgrade = UpgradesSc->currentLevel[unit->playerId][ScUpgrade::LegEnhancements];
		else
		if(unit->id == UnitId::ProtossScout)
			bSpeedUpgrade = UpgradesSc->currentLevel[unit->playerId][ScUpgrade::GraviticThrusters];
		else
		if(unit->id == UnitId::ProtossShuttle)
			bSpeedUpgrade = UpgradesSc->currentLevel[unit->playerId][ScUpgrade::GraviticDrive];
		else
		if(unit->id == UnitId::ProtossObserver)
			bSpeedUpgrade = UpgradesSc->currentLevel[unit->playerId][ScUpgrade::GraviticBoosters];
		else
		if(unit->id == UnitId::ZergUltralisk)
			bSpeedUpgrade = UpgradesSc->currentLevel[unit->playerId][BwUpgrade::AnabolicSynthesis];
		else
		if(unit->id == UnitId::Hero_Torrasque)
			bSpeedUpgrade = *IS_BROOD_WAR;
		else
		if(
			unit->id == UnitId::Hero_HunterKiller ||
			unit->id == UnitId::Hero_Yggdrasill ||
			unit->id == UnitId::Hero_FenixZealot ||
			unit->id == UnitId::Hero_Mojo ||
			unit->id == UnitId::Hero_Artanis ||
			unit->id == UnitId::ZergLurker
		)
			bSpeedUpgrade = 1;


		if(bSpeedUpgrade == 1) {
			unit->status |=UnitStatus::SpeedUpgrade;
			unit->updateSpeed();
		}

		if(bCooldownUpgrade == 1) {
			unit->status |=UnitStatus::CooldownUpgrade;
			unit->updateSpeed();
		}

		unit->updateSpeed();

	} //if(unit->id >= UnitId::TerranVulture && unit->id <= UnitId::ZergLurker)

}

;

//This function is called when an upgrade is finished, or when transferring a
//unit's ownership from one player to another (via triggers or Mind Control).
void applyUpgradeFlagsToExistingUnitsHook(CUnit* unit, u8 upgradeId) {

	const u32 UnitUpgradeRestrictionProc =		0x00453DC0;
	const u32 UltraliskUpgradeRestrictionProc = 0x00454070;
	const u32 VultureUpgradeRestrictionProc =	0x00454090;

	bool bCooldownUpgrade = false;	//[EBP-01]
	bool bSpeedUpgrade = true;		//[EBP-02]

	if(upgradeId >= UpgradeId::IonThrusters && upgradeId <= UpgradeId::AnabolicSynthesis) {

		u32 unitTypeUpgradedId;
		u32 Func_UpgradeRestrictionProc = NULL;

		if(upgradeId == UpgradeId::IonThrusters) {
			Func_UpgradeRestrictionProc = VultureUpgradeRestrictionProc;
			unitTypeUpgradedId = UnitId::TerranVulture;
		}else
		if(upgradeId == UpgradeId::PneumatizedCarapace) {
			Func_UpgradeRestrictionProc = UnitUpgradeRestrictionProc;
			unitTypeUpgradedId = UnitId::ZergOverlord;
		}else
		if(upgradeId == UpgradeId::MetabolicBoost) {
			Func_UpgradeRestrictionProc = UnitUpgradeRestrictionProc;
			unitTypeUpgradedId = UnitId::ZergZergling;
		}else
		if(upgradeId == UpgradeId::AdrenalGlands) {
			Func_UpgradeRestrictionProc = UnitUpgradeRestrictionProc;
			unitTypeUpgradedId = UnitId::ZergZergling;
			bCooldownUpgrade = true;
			bSpeedUpgrade = false;
		}else
		if(upgradeId == UpgradeId::MuscularAugments) {
			Func_UpgradeRestrictionProc = UnitUpgradeRestrictionProc;
			unitTypeUpgradedId = UnitId::ZergHydralisk;
		}else
		if(upgradeId == UpgradeId::LegEnhancements) {
			Func_UpgradeRestrictionProc = UnitUpgradeRestrictionProc;
			unitTypeUpgradedId = UnitId::ProtossZealot;
		}else
		if(upgradeId == UpgradeId::GraviticThrusters) {
			Func_UpgradeRestrictionProc = UnitUpgradeRestrictionProc;
			unitTypeUpgradedId = UnitId::ProtossScout;
		}else
		if(upgradeId == UpgradeId::GraviticDrive) {
			Func_UpgradeRestrictionProc = UnitUpgradeRestrictionProc;
			unitTypeUpgradedId = UnitId::ProtossShuttle;
		}else
		if(upgradeId == UpgradeId::GraviticBoosters) {
			Func_UpgradeRestrictionProc = UnitUpgradeRestrictionProc;
			unitTypeUpgradedId = UnitId::ProtossObserver;
		}else
		if(upgradeId == UpgradeId::AnabolicSynthesis) {
			Func_UpgradeRestrictionProc = UltraliskUpgradeRestrictionProc;
			unitTypeUpgradedId = UnitId::ZergUltralisk;
		}

		if(Func_UpgradeRestrictionProc != NULL) {
			
			CUnit* current_unit = firstPlayerUnit->unit[unit->playerId];

			while(current_unit != NULL) {

				//check if the upgrade apply to current unit
				if(upgradeRestrictionProc(current_unit,unitTypeUpgradedId,Func_UpgradeRestrictionProc)) {

					if(bCooldownUpgrade)
						current_unit->status |= UnitStatus::CooldownUpgrade;

					if(bSpeedUpgrade) {
						current_unit->status |= UnitStatus::SpeedUpgrade;
						current_unit->updateSpeed();
					}
					
				}

				current_unit = current_unit->player_link.next;

			} //while(current_unit != NULL)

		} //if(Func_UpgradeRestrictionProc != NULL)

	} //if(upgradeId >= UpgradeId::IonThrusters && upgradeId <= UpgradeId::AnabolicSynthesis)

}

;

} //hooks

//-------- Helper function definitions. Do NOT modify! --------//

namespace {

bool upgradeRestrictionProc(CUnit* unit, u8 upgradeId, u32 Func_UpgradeRestrictionProc) {

	static u32 bPreResult;

	__asm {
		PUSHAD
		MOVZX EDX, upgradeId
		MOV ECX, unit
		CALL Func_UpgradeRestrictionProc
		MOV bPreResult, EAX
		POPAD
	}

	return (bPreResult != 0);

}

} //Unnamed namespace

//End of helper functions
