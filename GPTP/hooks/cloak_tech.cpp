#include "cloak_tech.h"
#include "../SCBW/enumerations/UnitId.h"
#include "../SCBW/enumerations/TechId.h"

//V241 for VS2008

namespace hooks {

//Returns the tech ID used by this unit for the cloaking spell.
//For the cloaking energy consumption, see energy_regeneration.cpp
u8 getCloakingTech(const CUnit *unit) {
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

} //hooks