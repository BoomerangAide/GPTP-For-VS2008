#include "detector.h"
#include "../SCBW/scbwdata.h"
#include "../SCBW/enumerations.h"

namespace hooks {

/// Determines whether this unit can detect cloaked/burrowed units.
/// This affects CUnit::canDetect().
/// This overrides the EXE edit settings for Detectors in FireGraft.
bool unitCanDetectHook(CUnit* unit) {

	return (
		units_dat::BaseProperty[unit->id] & UnitProperty::Detector &&
		unit->status & UnitStatus::Completed &&
		!(unit->status & UnitStatus::DoodadStatesThing) &&
		unit->lockdownTimer == 0 &&
		unit->stasisTimer == 0 &&
		unit->maelstromTimer == 0 &&
		unit->isBlind == 0
	);

}

//Check related to the question of the @p detector being able to see the @p param->target 
//(assuming target is cloaked).
//Used in a IterateUnitsAtLocation function (thus the special structure)
//Part of a bigger logic, probably should not be touched
void getCloakedTargetVisibility(CUnit* detector, DetectorCheckParam* param) {

	CUnit* target = param->target;

	if(
		!(detector->status & UnitStatus::IsHallucination) &&	//hallucinations cannot detect
		detector->canDetect() &&								//detector must be in a state to detect
		detector != target										//detector don't try to detect itself
	) 
	{

		u8 visibilityFlags = (1 << detector->playerId);

		//only continue if the target sprite is visible (else it's
		//not a cloaking issue that hide the unit)
		if(target->sprite->visibilityFlags & visibilityFlags) {

			u32 detectionRange;

			if(detector->status & UnitStatus::GroundedBuilding)
				detectionRange = 224; //0xE0, 32 * 7
			else
				detectionRange = 32 * detector->getSightRange(false);

			if(detector->isTargetWithinMinRange(target,detectionRange)) {

				//update visionFlags for current target eval
				param->visionFlags |= 
					detector->parasiteFlags |					//detector's parasites player owner flags (8 bits)
					playerVision->flags[detector->playerId] |	//default visibility (32 bits)
					visibilityFlags								//detector's player flag (8 bits)
				;

			}

		}

	}

}

} //hooks
