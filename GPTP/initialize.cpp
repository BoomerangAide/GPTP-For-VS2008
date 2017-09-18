#include "definitions.h"
#include "Plugin.h"
#include "hook_tools.h"

//Hook header files
#include "hooks/game_hooks.h"
#include "graphics/draw_hook.h"

#include "hooks/apply_upgrade_flags.h"
#include "hooks/attack_priority.h"
#include "hooks/bunker_hooks.h"
#include "hooks/cloak_nearby_units.h"
#include "hooks/cloak_tech.h"
#include "hooks/detector.h"
#include "hooks/harvest.h"
#include "hooks/rally_point.h"
#include "hooks/recharge_shields.h"
#include "hooks/spider_mine.h"
#include "hooks/stim_packs.h"
#include "hooks/tech_target_check.h"
#include "hooks/transfer_tech_upgrades.h"
#include "hooks/unit_speed.h"
#include "hooks/update_status_effects.h"
#include "hooks/update_unit_state.h"
#include "hooks/weapons/weapon_cooldown.h"
#include "hooks/weapons/weapon_damage.h"
#include "hooks/weapons/weapon_fire.h"

#include "hooks/unit_destructor_special.h"
#include "hooks/psi_field.h"

#include "hooks/unit_stats/armor_bonus.h"
#include "hooks/unit_stats/sight_range.h"
#include "hooks/unit_stats/max_energy.h"
#include "hooks/unit_stats/weapon_range.h"
#include "hooks/interface/weapon_armor_tooltip.h"

//in alphabetical order
#include "hooks/orders/base_orders/attack_orders.h"
#include "hooks/interface/btns_cond.h"
#include "hooks/orders/building_making/building_morph.h"
#include "hooks/interface/buttonsets.h"
#include "hooks/orders/building_making/building_protoss.h"
#include "hooks/orders/building_making/building_terran.h"
#include "hooks/burrow_tech.h"
#include "hooks/orders/spells/cast_order.h"
#include "hooks/create_init_units.h"
#include "hooks/orders/base_orders/die_order.h"
#include "hooks/orders/enter_nydus.h"
#include "hooks/orders/spells/feedback_spell.h"
#include "hooks/give_unit.h"
#include "hooks/orders/spells/hallucination_spell.h"
#include "hooks/orders/infestation.h"
#include "hooks/orders/larva_creep_spawn.h"
#include "hooks/orders/liftland.h"
#include "hooks/orders/load_unload_orders.h"
#include "hooks/load_unload_proc.h"
#include "hooks/orders/building_making/make_nydus_exit.h"
#include "hooks/orders/medic_orders.h"
#include "hooks/orders/merge_units.h"
#include "hooks/orders/spells/nuke_orders.h"
#include "hooks/orders/spells/recall_spell.h"
#include "hooks/recv_commands/receive_command.h"
#include "hooks/orders/research_upgrade_orders.h"
#include "hooks/interface/selection.h"
#include "hooks/orders/siege_transform.h"
#include "hooks/orders/base_orders/stopholdpos_orders.h"
#include "hooks/recv_commands/train_cmd_receive.h"
#include "hooks/orders/unit_making/unit_morph.h"
#include "hooks/orders/unit_making/unit_train.h"
#include "hooks/interface/wireframe.h"
#include "hooks/weapons/wpnspellhit.h"

//#include "AI/spellcasting.h"

/// This function is called when the plugin is loaded into StarCraft.
/// You can enable/disable each group of hooks by commenting them.
/// You can also add custom modifications to StarCraft.exe by using:
///		memoryPatch(address_to_patch, value_to_patch_with);

BOOL WINAPI Plugin::InitializePlugin(IMPQDraftServer *lpMPQDraftServer) {

	//StarCraft.exe version check
	char exePath[300];
	const DWORD pathLen = GetModuleFileName(NULL, exePath, sizeof(exePath));

	if (pathLen == sizeof(exePath)) {
		MessageBox(NULL, "Error: Cannot check version of StarCraft.exe. The file path is too long.", NULL, MB_OK);
		return FALSE;
	}

	if (!checkStarCraftExeVersion(exePath))
		return FALSE;

	hooks::injectGameHooks();
	hooks::injectDrawHook();

	//in order of creation
	hooks::injectInfestationHooks();
	hooks::injectSiegeTransformHooks();
	hooks::injectButtonSetHooks();
	hooks::injectSelectMod();
	hooks::injectMergeUnitsHooks();
	hooks::injectLarvaCreepSpawnHooks();
	hooks::injectLiftLandHooks();
	hooks::injectAttackOrdersHooks();
	hooks::injectStopHoldPosOrdersHooks();
	hooks::injectRecallSpellHooks();
	hooks::injectEnterNydusHooks();
	hooks::injectCastOrderHooks();
	hooks::injectWpnSpellHitHooks();
	hooks::injectBuildingMorphHooks();
	hooks::injectMakeNydusExitHook();
	hooks::injectUnitMorphHooks();
	hooks::injectWireframeHook();
	hooks::injectDieOrderHook();
	hooks::injectBuildingTerranHook();
	hooks::injectBuildingProtossHooks();
	hooks::injectUnitTrainHooks();
	hooks::injectLoadUnloadProcHooks();
	hooks::injectLoadUnloadOrdersHooks();
	hooks::injectNukeOrdersHooks();
	hooks::injectBurrowTechHooks();
	hooks::injectResearchUpgradeOrdersHooks();
	hooks::injectMedicOrdersHooks();
	hooks::injectHallucinationSpellHook();
	hooks::injectFeedbackSpellHook();	
	hooks::injectBtnsCondHook();
	hooks::injectRecvCmdHook();
	hooks::injectCreateInitUnitsHooks();
	hooks::injectGiveUnitHook();
	hooks::injectTrainCmdRecvHooks();

	hooks::injectApplyUpgradeFlags();
	hooks::injectAttackPriorityHooks();
	hooks::injectBunkerHooks();
	hooks::injectCloakNearbyUnits();
	hooks::injectCloakingTechHooks();
	hooks::injectDetectorHooks();
	hooks::injectHarvestResource();
	hooks::injectRallyHooks();
	hooks::injectRechargeShieldsHooks();
	hooks::injectSpiderMineHooks();
	hooks::injectStimPacksHooks();
	hooks::injectTechTargetCheckHooks();
	hooks::injectTransferTechAndUpgradesHooks();
	hooks::injectUnitSpeedHooks();
	hooks::injectUpdateStatusEffects();
	hooks::injectUpdateUnitState();
	hooks::injectWeaponCooldownHook();
	hooks::injectWeaponDamageHook();
	hooks::injectWeaponFireHooks();
	
	hooks::injectUnitDestructorSpecial();
	hooks::injectPsiFieldHooks();
	
	hooks::injectArmorBonusHook();
	hooks::injectSightRangeHook();
	hooks::injectUnitMaxEnergyHook();
	hooks::injectWeaponRangeHooks();
	
	hooks::injectUnitTooltipHook();

	//hooks::injectSpellcasterAI();

	return TRUE;
}
