
//Helpers functions for hooks
//Result of study for functions,
//but is partial.
//Maybe can be injected, but
//this is disabled by default
//and it would require more
//checks to make sure it would
//work in all cases.

#pragma once
#include <SCBW/scbwdata.h>
#include <SCBW/enumerations.h>
#include <SCBW/api.h>
#include "Unitfinder.h"

namespace helpers {

	void disconnectAddOn_Sub464930(CUnit* unit);										//00464930  sub_464930
	void removeUnitRefsFromTarget(CUnit* unit, CUnit* target);							//0049E590  sub_49E590
	void readUnitsArray_Sub49EFA0(CUnit *unit, u8 playerId_param, u32 unknown_param);	//0049EFA0  sub_49EFA0
	void ordersRescuePassive(CUnit* unit);												//004A1EF0  orders_RescuePassive
	void changeUnitButtonSet(CUnit *unit, u16 buttonSetId);								//004E5D60  sub_4E5D60 
	void hideAndDisableUnit(CUnit *unit);												//004E6340  unitDeathSomething_0
	void showAndEnableUnit(CUnit *unit);												//004E6490  initUnitTrapDoodad
	void setNextWaypoint_Sub4EB290(CUnit *unit);										//004EB290  sub_4EB290

}

namespace {

//Originally 00464930  sub_464930
void __declspec(naked) disconnectAddOn_Sub464930Wrapper() {

	static CUnit* unit;

	__asm {
		PUSHAD
		MOV unit, EAX
	}

	helpers::disconnectAddOn_Sub464930(unit);

	__asm POPAD

}

//Originally 0049E590  sub_49E590
void __declspec(naked) removeUnitRefsFromTargetWrapper() {

	static CUnit* unit;
	static CUnit* target;

	__asm {

		PUSHAD
		MOV EBP, ESP
		SUB ESP, 0x08

		MOV EAX, [EBP+0x08]

		MOV unit, EAX

		XOR EAX, EAX

		MOV target, ECX

	}

	helpers::removeUnitRefsFromTarget(unit, target);

	__asm {
		POPAD
		RET 0x0004
	}

}


//Originally 0049EFA0  sub_49EFA0
void __declspec(naked) readUnitsArray_Sub49EFA0Wrapper() {

	static CUnit* unit;
	static u8 playerId;
	static u32 unknown_param;

  __asm {

    PUSHAD

	MOV EBP, ESP
	SUB ESP, 0x08

	XOR EAX, EAX
	MOV AL, [EBP+0x08]
	MOV playerId, AL

	MOV EAX, [EBP+0x0C]
	MOV unknown_param, EAX

	MOV unit, ECX

  }

  helpers::readUnitsArray_Sub49EFA0(unit, playerId, unknown_param);

  __asm {
	  POPAD
	  RET 0x0008
  }

}


//Originally 004A1EF0 orders_RescuePassive
void __declspec(naked) ordersRescuePassive() {

	static CUnit* unit;

	__asm {
		PUSHAD
		MOV EBP, ESP
		MOV unit, EAX
	}

	helpers::ordersRescuePassive(unit);

	__asm {
		POPAD
		RETN
	}


}
//Originally 004E5D60 sub_4E5D60
void __declspec(naked) changeUnitButtonSetWrapper() {

	static CUnit* unit;
	static u16 buttonSetId;

	__asm {
		PUSHAD
		MOV unit, EAX
		MOV buttonSetId, CX
	}

	helpers::changeUnitButtonSet(unit, buttonSetId);

	__asm POPAD

}
//Originally 004E6340 unitDeathSomething_0
void __declspec(naked) unitDeathSomething0Wrapper() {

	static CUnit* unit;

	__asm {
		PUSHAD
		MOV unit, EAX
	}

	helpers::hideAndDisableUnit(unit);

	__asm POPAD

}


//Originally 004E6490 initUnitTrapDoodad
void __declspec(naked) showAndEnableUnitWrapper() {

	static CUnit *unit;

	__asm {
		PUSHAD
		MOV unit, EDI
	}

	helpers::showAndEnableUnit(unit);

    __asm POPAD

}




//Originally 004EB290  sub_4EB290
void __declspec(naked) setNextWaypoint_Sub4EB290Wrapper() {

	static CUnit* unit;

	__asm {
		PUSHAD
		MOV EBP, ESP
		MOV unit, EAX
	}

	helpers::setNextWaypoint_Sub4EB290(unit);

	__asm {
		POPAD
		RETN
	}


}

} //end of unnamed namespace
