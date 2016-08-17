/// Support for adding/removing psi fields. To use, you will also have to modify
/// the following hooks:
///
///   hooks/unit_destructor_special.cpp
///   hooks/unit_selection_graphics.cpp

//NOT FULLY REVALIDATED BY UNDEADSTAR

#pragma once
#include "../SCBW/structures/CUnit.h"

namespace hooks {

/// Edit these functions in psi_field.cpp.
bool isReadyToMakePsiField(CUnit* unit);
bool canMakePsiField(u16 unitId);

/// This function must be called once per frame in nextFrame().
/// This uses canMakePsiField() and isReadyToMakePsiField() internally.
void updatePsiFieldProviders();

//Call this in initialize.h.
void injectPsiFieldHooks();

} //hooks
