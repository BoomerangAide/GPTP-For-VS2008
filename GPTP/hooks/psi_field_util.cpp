//All functions in this file are meant to be hook helpers for psi_field.h.
//Do NOT modify any functions in this file!

#include "psi_field.h"
#include "../SCBW/scbwdata.h"
#include <algorithm>
#include <cassert>

//NOT FULLY REVALIDATED BY UNDEADSTAR

//-------- Unit id safeguard --------//

//Checks if the given unit ID can provide psi (for use in assertion)
//The following unit types cannot make psi fields
//  workers, factories, resource containers, ghosts, nydus canals, silos,
//  hatcheries, and powerups
bool isValidPsiProviderType(u16 unitId) {

	if (unitId >= UNIT_TYPE_COUNT) 
		return false;

	//Uses memory space of CUnit::building for other purposes
	if (units_dat::BaseProperty[unitId] & (UnitProperty::Worker | UnitProperty::ResourceContainer | UnitProperty::NPCOrAccessories))
		return false;

	//CUnit::rally shares memory space with CUnit::psi_link
	if (units_dat::GroupFlags[unitId].isFactory) 
		return false;

	//Uses memory space of CUnit::building for other purposes
	if (	unitId == UnitId::ghost ||
			unitId == UnitId::sarah_kerrigan ||
			unitId == UnitId::Hero_AlexeiStukov ||
			unitId == UnitId::Hero_SamirDuran ||
			unitId == UnitId::Hero_InfestedDuran ||
			unitId == UnitId::nydus_canal ||
			unitId == UnitId::nuclear_silo ||
			unitId == UnitId::hatchery  ||
			unitId == UnitId::lair ||
			unitId == UnitId::hive
	 )
		return false;

	return true;

}

//-------- Add psi field --------//

//AKA createPsiFieldSpriteForUnit()
//Returns true if successful, false otherwise.
bool addPsiFieldSprite(CUnit* unit) {
  if (!unit) return false;

  const u32 Func_addPsiFieldSprite = 0x00493BF0;
  static u32 result;

  __asm {
    PUSHAD
    MOV ECX, unit
    CALL Func_addPsiFieldSprite
    MOV result, EAX
    POPAD
  }

  return result != 0;
}

//Adds @p unit to the psi provider list and creates the psi field sprite.
//Based on orders_InitPsiProvider() @ 00493F70
//But this does not affect the unit's current order.
void addPsiField(CUnit* unit) {
  if (!unit) return;

  if (*firstPsiFieldProvider == unit || unit->psi_link.next || unit->psi_link.prev)
    return;

  unit->psi_link.prev = NULL;
  unit->psi_link.next = *firstPsiFieldProvider;
  if (*firstPsiFieldProvider)
    (*firstPsiFieldProvider)->psi_link.prev = unit;
  *firstPsiFieldProvider = unit;
  addPsiFieldSprite(unit);
  *canUpdatePoweredStatus = true;
}


//-------- Remove psi field --------//

//Identical to function @ 0x00493100
void removeFromPsiProviderList(CUnit* psiProvider) {
  if (psiProvider->psi_link.prev)
    psiProvider->psi_link.prev->psi_link.next = psiProvider->psi_link.next;
  if (psiProvider->psi_link.next)
    psiProvider->psi_link.next->psi_link.prev = psiProvider->psi_link.prev;

  if (psiProvider == *firstPsiFieldProvider)
    *firstPsiFieldProvider = psiProvider->psi_link.next;

  psiProvider->psi_link.prev = NULL;
  psiProvider->psi_link.next = NULL;
}

//Removes @p unit from the psi provider list and destroys the psi field sprite.
void removePsiField(CUnit* unit) {
  if (unit->building.pylonAura) {
    unit->building.pylonAura->free();
    unit->building.pylonAura = NULL;
    *canUpdatePoweredStatus = true;   //Might work?
  }
  removeFromPsiProviderList(unit);
}

//-------- Update psi field position --------//

void refreshSpriteData(CSprite *sprite) {
  const u32 Func_refreshSpriteData = 0x004983A0;

  __asm {
    PUSHAD
    MOV EAX, sprite
    CALL Func_refreshSpriteData
    POPAD
  }
}

//Synchronizes the unit's psi field sprite position with the unit.
void updatePsiFieldPosition(CUnit* unit) {
  if (!unit || !unit->sprite || !unit->building.pylonAura) return;

  CSprite *psiField = unit->building.pylonAura;
  if (unit->sprite->position != psiField->position) {
    //for (CImage *i = psiField->imageHead; i; i = i->link.next)
    //  i->flags |= 1;  //Redraw image

    psiField->setPosition(unit->getX(), unit->getY());
    refreshSpriteData(psiField);
    *canUpdatePoweredStatus = true;
  }
}

//-------- Update psi field provider --------//

//Defined in psi_field_inject.cpp
void hideAllPsiFields();

namespace hooks {

void updatePsiFieldProviders() {

	for (CUnit* unit = *firstVisibleUnit; unit; unit = unit->link.next) {

		if (hooks::canMakePsiField(unit->id)) {

			assert(isValidPsiProviderType(unit->id));

			if (unit->status & UnitStatus::Completed) {

				if (hooks::isReadyToMakePsiField(unit)) {
					addPsiField(unit);
					updatePsiFieldPosition(unit);
				}

				else
				  removePsiField(unit);
			}

		}

	}

	if (!(*IS_PLACING_BUILDING)) {

		CUnit* selUnit;

		for (int i = 0; i < SELECTION_ARRAY_LENGTH; i++) {

			selUnit = clientSelectionGroup->unit[i];

			if (selUnit != NULL && hooks::isReadyToMakePsiField(selUnit))
				return;

		}

		hideAllPsiFields();

	}

} //void updatePsiFieldProviders()

} //hooks
