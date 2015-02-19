#include "cloak_tech.h"
#include "../SCBW/scbwdata.h"
#include "../SCBW/api.h"
#include "../hook_tools.h"

//V241 for VS2008

/*

There are 9 places where StarCraft checks unit ID for cloaking.

* 0x00429210: BTNSCOND_IsCloaked  (Used by Infested Kerrigan, Infested Duran, and Mixed Cloakable Group)
* 0x004292C0: BTNSCOND_CanCloak   (Used by Infested Kerrigan, Infested Duran, and Mixed Cloakable Group)
* 0x00491B30: ApplyCloakingOrder  (Used by all spell-cloaking units)
* 0x004C0720: CMDRECV_Cloak       (Used by all spell-cloaking units)
* 0x0043B970: AI_orderUnitCloaking(Used by AI-controlled units)
* 0x004C0660: CMDRECV_Decloak     (Used by all spell-cloaking units)
* 0x00491A50: getCloakingTech     (Used by "Create Unit With Properties" in StarEdit + create_unit opcode in aiscript.bin)
* 0x00491A90: getCloakingEnergyConsumption (Used by energy regen; This is editable from the energy hook stuff)
* 0x00423540: currentUnitSelectionCanCloak(Called by CMDACT_Cloak for all units; also checks energy amount)

Note that Wraiths and Ghosts use BTNSCOND_CanCloak_0 and BTNSCOND_IsCloaked_0,
which does NOT check unit IDs at all. (FireGraft has it wrong when it says that
Wraiths use "Can Cloak" and Infested Kerrigan uses "Can Cloak - Mixed")

*/

namespace {

//-------- Button conditions --------//

Bool32 __fastcall cloakingTechWrapper_IsCloaked(u32 _unused, s32 playerId) {
  for (int i = 0; i < 12; ++i) {
    CUnit *unit = clientSelectionGroup->unit[i];
    if (unit != NULL) {
      if (unit->canUseTech(hooks::getCloakingTech(unit), playerId) != 1)
        return false;

      if (unit->status & UnitStatus::CloakingForFree
        && !(unit->status & UnitStatus::Burrowed))
        return false;

      if (!(unit->status & UnitStatus::RequiresDetection))
        return false;
    }
  }

  return true;
}

Bool32 __fastcall cloakingTechWrapper_CanCloak(u32 _unused, s32 playerId) {
  for (int i = 0; i < 12; ++i) {
    CUnit *unit = clientSelectionGroup->unit[i];
    if (unit != NULL) {
      if (unit->canUseTech(hooks::getCloakingTech(unit), playerId) != 1)
        continue;

      if (unit->status & UnitStatus::CloakingForFree
          && !(unit->status & UnitStatus::Burrowed))
        continue;

      if (unit->status & UnitStatus::RequiresDetection)
        continue;

      return true;
    }
  }

  return false;
}

//-------- Actual cloak orders --------//

void applyCloakingOrderHook(CUnit *unit) {
  if (unit->status & UnitStatus::RequiresDetection)
    return;

  const u16 energyCost = techdata_dat::EnergyCost[hooks::getCloakingTech(unit)] * 256;
  if (scbw::isCheatEnabled(CheatFlags::TheGathering) || unit->energy >= energyCost) {
    if (!scbw::isCheatEnabled(CheatFlags::TheGathering))
      unit->energy -= energyCost;

    unit->setSecondaryOrder(OrderId::Cloak);
  }
}

void __cdecl cloakingTechWrapper_CMDRECV_Cloak() {
  *selectionIndexStart = 0;  
  while (CUnit *unit = getActivePlayerNextSelection()) {
    if (unit->canUseTech(hooks::getCloakingTech(unit), *ACTIVE_NATION_ID) == 1)
      applyCloakingOrderHook(unit);
  }
}

void __declspec(naked) cloakingTechWrapper_AI_cloakUnit() {
  static CUnit *unit;
  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV unit, ESI
  }

  if (!(unit->status & UnitStatus::RequiresDetection)) {
    if (unit->canUseTech(hooks::getCloakingTech(unit), unit->playerId) == 1)
      applyCloakingOrderHook(unit);
  }

  __asm {
    POPAD
    RETN
  }
}

void __cdecl cloakingTechWrapper_CMDRECV_Decloak() {
  *selectionIndexStart = 0;
  while (CUnit *unit = getActivePlayerNextSelection()) {
    if (unit->canUseTech(hooks::getCloakingTech(unit), *ACTIVE_NATION_ID) == 1)
      unit->setSecondaryOrder(OrderId::Decloak);
  }
}

//-------- Other wrappers --------//

void __declspec(naked) getCloakingTechWrapper() {
  static CUnit *unit;
  static u8 result;
  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV unit, EAX
  }

  result = hooks::getCloakingTech(unit);

  __asm {
    POPAD
    MOV AL, result
    RETN
  }
}

Bool32 __cdecl currentUnitSelectionCanCloakWrapper() {
  for (int i = 0; i < 12; ++i) {
    CUnit *unit = clientSelectionGroup->unit[i];
    if (unit != NULL) {
      if (scbw::isCheatEnabled(CheatFlags::TheGathering)
          || unit->energy >= techdata_dat::EnergyCost[hooks::getCloakingTech(unit)] * 256)
        return true;
    }
  }

  const RaceId::Enum race = (*activePortraitUnit)->getRace();

  scbw::showErrorMessageWithSfx((*activePortraitUnit)->playerId, 864 + race, 156 + race);
  return false;
}

} //unnamed namespace

namespace hooks {

void injectCloakingTechHooks() {
  jmpPatch(cloakingTechWrapper_IsCloaked,       0x00429210);
  jmpPatch(cloakingTechWrapper_CanCloak,        0x004292C0);
  jmpPatch(cloakingTechWrapper_CMDRECV_Cloak,   0x004C0720);
  jmpPatch(cloakingTechWrapper_AI_cloakUnit,    0x0043B970);
  jmpPatch(cloakingTechWrapper_CMDRECV_Decloak, 0x004C0660);
  jmpPatch(getCloakingTechWrapper,              0x00491A50);
  jmpPatch(currentUnitSelectionCanCloakWrapper, 0x00423540);
}

} //hooks