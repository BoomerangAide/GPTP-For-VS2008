#include "sight_range.h"
#include <SCBW/api.h>

const int DEFAULT_SIGHT_RANGE = 4;
const int BLIND_SIGHT_RANGE = 2;
const int MAX_SIGHT_RANGE = 11;

namespace hooks {

/// Returns the modified sight range of the unit, measured in matrices.
/// StarCraft passes 1 for isForSpellCasting when using Feedback, Mind Control,
/// and Hallucination (but not when launching Nukes).
/// Note: sight ranges cannot exceed 11, unless extended.
/// Equivalent to getUpgradedSightRange @ 004E5B40  
u32 getSightRangeHook(CUnit* unit, bool isForSpellCasting) {

	u32 sightRange;

	//Check if the unit is a constructing building (exclude remorphing buildings)
	if (	unit->status & UnitStatus::GroundedBuilding &&
			!(unit->status & UnitStatus::Completed) &&
			!unit->isRemorphingBuilding()
	)
		sightRange = DEFAULT_SIGHT_RANGE;
	else
	//Check if the unit is blinded (don't bother if this is for spellcasting)
	if (!isForSpellCasting && unit->isBlind)
		sightRange = BLIND_SIGHT_RANGE;
	else
	if(unit->id < UnitId::TerranGhost || unit->id > UnitId::ProtossObserver)
		sightRange = units_dat::SightRange[unit->id];
	else {
		
		if(
			unit->id == UnitId::TerranGhost && 
			UpgradesSc->currentLevel[unit->playerId][UpgradeId::OcularImplants] != 0
		)
			sightRange = MAX_SIGHT_RANGE;
		else
		if(
			unit->id == UnitId::ZergOverlord && 
			UpgradesSc->currentLevel[unit->playerId][UpgradeId::Antennae] != 0
		)
			sightRange = MAX_SIGHT_RANGE;
		else
		if(
			unit->id == UnitId::ProtossObserver && 
			UpgradesSc->currentLevel[unit->playerId][UpgradeId::SensorArray] != 0
		)
			sightRange = MAX_SIGHT_RANGE;
		else
		if(
			unit->id == UnitId::ProtossScout && 
			UpgradesSc->currentLevel[unit->playerId][UpgradeId::ApialSensors] != 0
		)
			sightRange = MAX_SIGHT_RANGE;
		else
			sightRange = units_dat::SightRange[unit->id];

	}

	return sightRange;

}

} //hooks
