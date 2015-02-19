#pragma once
#include "../SCBW/structures/CUnit.h"

//V241 for VS2008

namespace hooks {

void weaponDamageHook(s32     damage,
                      CUnit*  target,
                      u8      weaponId,
                      CUnit*  attacker,
                      u8      attackingPlayer,
                      s8      direction,
                      u8      dmgDivisor);

void injectWeaponDamageHook();

} //hooks
