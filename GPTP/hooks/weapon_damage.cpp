#include "weapon_damage.h"
#include "../SCBW/scbwdata.h"
#include "../SCBW/enumerations.h"
#include "../SCBW/api.h"
#include <algorithm>

//V241 for VS2008

namespace {
//Helper functions
void createShieldOverlay(CUnit *unit, u32 attackDirection);
u16 getUnitStrength(const CUnit *unit, bool useGroundStrength);

/// Definition of damage factors (explosive, concussive, etc.)
struct {
  s32 damageType;
  s32 unitSizeFactor[4];   //Order: {independent, small, medium, large}
} const damageFactor[5] = {
  {0, 0, 0, 0, 0},        //Independent
  {1, 0, 128, 192, 256},  //Explosive
  {2, 0, 256, 128, 64},   //Concussive
  {3, 0, 256, 256, 256},  //Normal
  {4, 0, 256, 256, 256}   //IgnoreArmor
};

} //unnamed namespace

namespace hooks {

/// Hooks into the CUnit::damageWith() function.
void weaponDamageHook(s32     damage,
                      CUnit*  target,
                      u8      weaponId,
                      CUnit*  attacker,
                      u8      attackingPlayer,
                      s8      direction,
                      u8      dmgDivisor) {
  //Default StarCraft behavior

  //Don't bother if the unit is already dead or invincible
  if (target->hitPoints == 0 || (target->status & UnitStatus::Invincible))
    return;

  if (scbw::isCheatEnabled(CheatFlags::PowerOverwhelming)         //If Power Overwhelming is enabled
      && playerTable[attackingPlayer].type != PlayerType::Human)  //and the attacker is not a human player
    damage = 0;

  if (target->status & UnitStatus::IsHallucination)
    damage *= 2;

  damage = damage / dmgDivisor + (target->acidSporeCount << 8);
  if (damage < 128)
    damage = 128;

  //Reduce Defensive Matrix
  if (target->defensiveMatrixHp) {
    const s32 d_matrix_reduceAmount = std::min<s32>(damage, target->defensiveMatrixHp);
    damage -= d_matrix_reduceAmount;
    target->reduceDefensiveMatrixHp(d_matrix_reduceAmount);
  }

  const u8 damageType = weapons_dat::DamageType[weaponId];

  //Reduce Plasma Shields...but not just yet
  s32 shieldReduceAmount = 0;
  if (units_dat::ShieldsEnabled[target->id] && target->shields >= 256) {
    if (damageType != DamageType::IgnoreArmor) {
      s32 plasmaShieldUpg = scbw::getUpgradeLevel(target->playerId, UpgradeId::ProtossPlasmaShields) << 8;
      if (damage > plasmaShieldUpg) //Weird logic, Blizzard dev must have been sleepy
        damage -= plasmaShieldUpg;
      else
        damage = 128;
    }
    shieldReduceAmount = std::min(damage, target->shields);
    damage -= shieldReduceAmount;
  }

  //Apply armor
  if (damageType != DamageType::IgnoreArmor) {
    const s32 armorTotal = target->getArmor() << 8;
    damage -= std::min(damage, armorTotal);
  }

  //Apply damage type/unit size factor
  damage = (damage * damageFactor[damageType].unitSizeFactor[units_dat::SizeType[target->id]]) >> 8;
  if (shieldReduceAmount == 0 && damage < 128)
    damage = 128;

  //Deal damage to target HP, killing it if possible
  target->damageHp(damage, attacker, attackingPlayer,
                   weaponId != WeaponId::Irradiate);    //Prevent Science Vessels from being continuously revealed to the irradiated target

  //Reduce shields (finally)
  if (shieldReduceAmount != 0) {
    target->shields -= shieldReduceAmount;
    if (damageType != DamageType::Independent && target->shields != 0)
      createShieldOverlay(target, direction);
  }

  //Update unit strength data (?)
  target->airStrength = getUnitStrength(target, false);
  target->groundStrength = getUnitStrength(target, true);
}

} //hooks

namespace {

/**** Definitions of helper functions. Do NOT modify anything below! ****/

//Creates the Plasma Shield flickering effect.
//Identical to function @ 0x004E6140
void createShieldOverlay(CUnit *unit, u32 attackDirection) {
  const LO_Header* shield_lo = shieldOverlays[unit->sprite->mainGraphic->id];
  u32 frameAngle = (attackDirection - 124) / 8 % 32;
  Point8 offset = shield_lo->getOffset(unit->sprite->mainGraphic->direction, frameAngle);
  unit->sprite->createOverlay(ImageId::ShieldOverlay, offset.x, offset.y, frameAngle);
}

//Somehow related to AI stuff; details unknown.
const u32 Helper_GetUnitStrength      = 0x00431800;
u16 getUnitStrength(const CUnit *unit, bool useGroundStrength) {
  u16 strength;
  u32 useGroundStrength_ = (useGroundStrength ? 1 : 0);

  __asm {
    PUSHAD
    PUSH useGroundStrength_
    MOV EAX, unit
    CALL Helper_GetUnitStrength
    MOV strength, AX
    POPAD
  }

  return strength;
}

} //unnamed namespace
