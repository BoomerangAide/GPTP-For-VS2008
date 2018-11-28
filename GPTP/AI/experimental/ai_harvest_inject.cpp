#include "ai_harvest.h"
#include <hook_tools.h>

namespace {

void __declspec(naked) harvestNextNearestResourcesExWrapper() {

  static CUnit* worker;
  static CUnit* mineral_field;
  static u16 x,y;
  static CUnit* return_value;

	__asm {
		PUSH EBP
		MOV EBP, ESP
		MOV mineral_field, EAX
		MOV EAX, [EBP+0x08]
		MOV worker, EAX
		MOV AX, [EBP+0x0C]
		MOV x, AX
		MOV AX, [EBP+0x0E]
		MOV y, AX
		PUSHAD
	}

	return_value = AI::harvestNextNearestResourcesEx(mineral_field,worker,x,y);

	__asm {
		POPAD
		MOV EAX, return_value
		POP EBP
		RETN 8
	}

}

;

void __declspec(naked) FindMineralFieldWrapper() {

	static CUnit* return_value;
	static u32 unk_resource_area;

	__asm {
		MOV unk_resource_area, EDX
		PUSHAD
	}

	return_value = AI::FindMineralField(unk_resource_area);

	__asm {
		POPAD
		MOV EAX, return_value
		RETN
	}

}

;

} //unnamed namespace

namespace hooks {

	void injectAI_HarvestHooks() {
		jmpPatch(harvestNextNearestResourcesExWrapper,	0x004432D0, 4);
		jmpPatch(FindMineralFieldWrapper,				0x004445E0, 0);
	}

}
