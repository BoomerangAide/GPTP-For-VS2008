#include "cloak_nearby_units.h"
#include <SCBW/UnitFinder.h>
#include <SCBW/api.h>
#include <algorithm>

//Helper functions
namespace {
void secondaryOrder_Cloak(CUnit* unit);
CUnit** getAllUnitsInBounds(Box16* coords);		//0x0042FF80
} //unnamed namespace

namespace hooks {

//Cloak all units near @p cloaker.
void cloakNearbyUnitsHook(CUnit* cloaker) {

	bool needsRefresh = false;

	static u16* const maxBoxRightValue =			(u16*) 0x00628450;	//should usually be mapTileSize->width * 32
	static u16* const maxBoxBottomValue =			(u16*) 0x006284B4;	//should usually be mapTileSize->height * 32

	Box16 area_of_effect;

	CUnit** unitsInAreaOfEffect;
	CUnit* current_unit;

	//Use the unit's air weapon range
	u32 cloakRadius = cloaker->getMaxWeaponRange(cloaker->getAirWeapon());

	area_of_effect.left = cloaker->sprite->position.x - cloakRadius;
	area_of_effect.right = cloaker->sprite->position.x + cloakRadius;
	area_of_effect.top = cloaker->sprite->position.x - cloakRadius;
	area_of_effect.bottom = cloaker->sprite->position.x - cloakRadius;

	if(area_of_effect.left < 0)
		area_of_effect.left = 0;
	if(area_of_effect.top < 0)
		area_of_effect.top = 0;
	if(area_of_effect.right > *maxBoxRightValue)
		area_of_effect.right = *maxBoxRightValue;
	if(area_of_effect.bottom > *maxBoxBottomValue)
		area_of_effect.bottom = *maxBoxBottomValue;

	unitsInAreaOfEffect = getAllUnitsInBounds(&area_of_effect);

	current_unit = unitsInAreaOfEffect[0];

	while(current_unit != NULL) {

		if (
			current_unit->id != UnitId::arbiter &&
			current_unit->id != UnitId::danimoth &&
			!(units_dat::BaseProperty[current_unit->id] & UnitProperty::Building) &&	//Don't cloak buildings
			!(current_unit->status & UnitStatus::IsHallucination) &&					//Don't cloak hallucinations
			!(current_unit->status & UnitStatus::CloakingForFree) &&					//Don't cloak already cloaking for free units
			current_unit->id != UnitId::nuclear_missile &&								//Don't cloak nukes
			current_unit->mainOrderId != OrderId::Warpin &&								//Don't cloak units doing order WarpIn
			cloaker->playerId == current_unit->playerId	&&								//Unit owner must be Cloaker owner
			cloaker->isTargetWithinMinRange(current_unit,cloakRadius)					//Check again if unit in range of cloaking
		)
		{
			secondaryOrder_Cloak(current_unit);
			current_unit->status |= UnitStatus::CloakingForFree;
			needsRefresh = true;
		}

		current_unit = current_unit->link.next;

	}

	*tempUnitsListCurrentArrayCount = tempUnitsListArraysCountsListLastIndex[*tempUnitsListArraysCountsListLastIndex];
	*tempUnitsListArraysCountsListLastIndex = *tempUnitsListArraysCountsListLastIndex - 1;

	if (needsRefresh)
		scbw::refreshConsole();

}

} //hooks

/**** Helper function definitions. Do not change anything below this! ****/

namespace {

//Identical to secondaryOrd_Cloak @ 0x00491790
void secondaryOrder_Cloak(CUnit* unit) {

	static CUnit** const firstBurrowedUnit = (CUnit**) 0x0063FF5C;

	if (
		!unit->isCloaked &&
		!(unit->status & UnitStatus::RequiresDetection) &&
		unit->burrow_link.next == NULL
	)
	{

		unit->isCloaked = true;

		unit->burrow_link.next = *firstBurrowedUnit;
		unit->burrow_link.prev = NULL;

		if (*firstBurrowedUnit != NULL)
			(*firstBurrowedUnit)->burrow_link.prev = unit;

		*firstBurrowedUnit = unit;

		scbw::refreshConsole();

	}

}

;

const u32 Func_GetAllUnitsInBounds = 0x0042FF80;
CUnit** getAllUnitsInBounds(Box16* coords) {

	static CUnit** units_in_bounds;

	__asm {
		PUSHAD
		MOV EAX, coords
		CALL Func_GetAllUnitsInBounds
		MOV units_in_bounds, EAX
		POPAD
	}

	return units_in_bounds;

}

;

} //unnamed namespace
