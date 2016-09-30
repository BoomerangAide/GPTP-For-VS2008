//Common functions used by the AI.
#pragma once
#include "../SCBW/UnitFinder.h"
#include "../SCBW/structures/CUnit.h"
#include "../SCBW/api.h"

namespace AI {

bool isTargetWorthHitting(CUnit* target, CUnit* attacker);

/// Returns true if @p target is attacking a player allied to @p unit.
bool isTargetAttackingAlly(CUnit* target, CUnit* unit);

/// Determines whether the given @p playerId is in a UMS map (i.e. campaign mode).
bool isUmsMode(u8 playerId);

/// Determines if the @p unit is within a region that is not commanded by its
/// controlling AI. Details are not really understood.
bool isUnitInUnsafeRegion(CUnit* unit);

int getTotalEnemyLifeInArea(int x, int y, int searchBounds, CUnit* caster, u8 weaponId);
int getTotalAllyLifeInArea(int x, int y, int searchBounds, CUnit* caster, u8 weaponId);
int getTotalEnemyShieldsInArea(int x, int y, int searchBounds, CUnit* caster);
int getTotalEnemyEnergyInArea(int x, int y, int searchBounds, CUnit* caster);
int getTotalEnemyNukeValueInArea(int x, int y, int searchBounds, CUnit* caster);

//-------- Template function definition --------//

} //AI