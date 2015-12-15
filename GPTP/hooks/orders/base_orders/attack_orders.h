#pragma once
#include "../../../SCBW/structures/CUnit.h"

namespace hooks {

void orders_ReaverAttack1(CUnit* unit);		//00465690
void orders_CarrierAttack1(CUnit* unit);	//00465950
void orders_TurretAttack(CUnit* unit);		//00477980
void orders_AttackFixedRange(CUnit* unit);	//00477D00
void orders_SapUnit(CUnit* unit);			//004788E0
void orders_SapLocation(CUnit* unit);		//00478A40
void orders_AttackMoveEP(CUnit* unit);		//00478DE0
void orders_AttackMove(CUnit* unit);		//00479040
void orders_AttackUnit(CUnit* unit);		//00479BD0

void injectAttackOrdersHooks();

} //hooks
