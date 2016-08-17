#include "cloak_tech.h"
#include <SCBW/scbwdata.h>

namespace hooks {

//Returns the tech ID used by this unit for the cloaking spell.
//For the cloaking energy consumption, see energy_regeneration.cpp
u8 getCloakingTech(CUnit* unit) {
  //Default StarCraft behavior

  if (unit->id == UnitId::ghost
    || unit->id == UnitId::sarah_kerrigan
    || unit->id == UnitId::Hero_AlexeiStukov
    || unit->id == UnitId::Hero_SamirDuran
    || unit->id == UnitId::Hero_InfestedDuran
    || unit->id == UnitId::Hero_InfestedKerrigan)
    return TechId::PersonnelCloaking;

  if (unit->id == UnitId::wraith || unit->id == UnitId::tom_kazansky)
    return TechId::CloakingField;

  return TechId::None;
  
}

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

Bool32 BTNSCOND_IsCloaked(CUnit* unit, u32 playerId, u16 reqVar) {
	
	Bool32 bReturnValue = TRUE;
	CUnit* unit_from_selection;


	for(int i = 0; i < SELECTION_ARRAY_LENGTH && (bReturnValue == TRUE); i++) {

		unit_from_selection = clientSelectionGroup->unit[i];

		if(unit_from_selection != NULL) {

			//original code is hardcoded, not using a function
			u8 techId = getCloakingTech(unit_from_selection); 

			if(unit_from_selection->canUseTech(techId,playerId) == TRUE) {

				if(
					unit_from_selection->status & UnitStatus::CloakingForFree &&
					!(unit_from_selection->status &  UnitStatus::Burrowed)
				)
					bReturnValue = FALSE;
				else 
				if(!(unit_from_selection->status & UnitStatus::RequiresDetection))
					bReturnValue = FALSE;

			}
			else
				bReturnValue = FALSE;

		}

	}

	return bReturnValue;

} //Bool32 BTNSCOND_IsCloaked(CUnit* unit, u32 playerId, u16 reqVar)

Bool32 BTNSCOND_CanCloak(CUnit* unit, u32 playerId, u16 reqVar) {
	
	Bool32 bReturnValue = FALSE;
	CUnit* unit_from_selection;

	for(int i = 0; i < SELECTION_ARRAY_LENGTH && (bReturnValue == FALSE); i++) {

		unit_from_selection = clientSelectionGroup->unit[i];

		if(unit_from_selection != NULL) {

			//original code is hardcoded, not using a function
			u8 techId = getCloakingTech(unit_from_selection); 

			if(
				unit_from_selection->canUseTech(techId,playerId) == TRUE &&				//must be able to use cloaking tech for more checks to be necessary
					(!(unit_from_selection->status & UnitStatus::CloakingForFree) ||	//to cloak, unit should not already be cloaked for free
					unit_from_selection->status &  UnitStatus::Burrowed) &&				//if burrowed, cloaking for free, but still allowed to cloak
				!(unit_from_selection->status & UnitStatus::RequiresDetection)			//if unit doesn't already require detection
			)
				bReturnValue = TRUE;

		}

	}

	return bReturnValue;

} //Bool32 BTNSCOND_CanCloak(CUnit* unit, u32 playerId, u16 reqVar)

} //hooks
