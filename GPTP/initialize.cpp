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
#include "hooks/consume.h"
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
#include "hooks/weapon_cooldown.h"
#include "hooks/weapon_damage.h"
#include "hooks/weapon_fire.h"

#include "hooks/unit_destructor_special.h"
#include "hooks/psi_field.h"

#include "hooks/unit_morph.h"
#include "hooks/building_morph.h"

#include "hooks/unit_stats/armor_bonus.h"
#include "hooks/unit_stats/sight_range.h"
#include "hooks/unit_stats/max_energy.h"
#include "hooks/unit_stats/weapon_range.h"
#include "hooks/interface/weapon_armor_tooltip.h"

#include "hooks/orders/infestation.h"
#include "hooks/orders/siege_transform.h"
#include "hooks/interface/buttonsets.h"
#include "hooks/interface/selection.h"
#include "hooks/orders/merge_units.h"
#include "hooks/orders/larva_creep_spawn.h"
#include "hooks/orders/liftland.h"
#include "hooks/orders/base_orders/attack_orders.h"

#include "AI/spellcasting.h"

/// This function is called when the plugin is loaded into StarCraft.
/// You can enable/disable each group of hooks by commenting them.
/// You can also add custom modifications to StarCraft.exe by using:
///    memoryPatch(address_to_patch, value_to_patch_with);

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
  
  hooks::injectInfestationHooks();
  hooks::injectSiegeTransformHooks();
  hooks::injectButtonSetHooks();
  hooks::injectSelectMod();
  hooks::injectMergeUnitsHooks();
  hooks::injectLarvaCreepSpawnHooks();
  hooks::injectLiftLandHooks();
  hooks::injectAttackOrdersHooks();

  hooks::injectApplyUpgradeFlags();
  hooks::injectAttackPriorityHooks();
  hooks::injectBunkerHooks();
  hooks::injectCloakNearbyUnits();
  hooks::injectCloakingTechHooks();
  hooks::injectConsumeHooks();
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

  hooks::injectUnitMorphHooks();
  hooks::injectBuildingMorphHooks();
  
  hooks::injectArmorBonusHook();
  hooks::injectSightRangeHook();
  hooks::injectUnitMaxEnergyHook();
  hooks::injectWeaponRangeHooks();
  
  hooks::injectUnitTooltipHook();

  hooks::injectSpellcasterAI();

  return TRUE;
}
