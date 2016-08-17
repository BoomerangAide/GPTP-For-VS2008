#include "harvest.h"
#include "../hook_tools.h"

void __declspec(naked) transferResourceToWorkerWrapper() {

	static CUnit* worker;
	static CUnit* resource;

	__asm {
		PUSH EBP
		MOV EBP, ESP
		MOV worker, ECX
		MOV resource, EAX
		PUSHAD
	}

	hooks::transferResourceToWorkerHook(worker, resource);

	__asm {
		POPAD
		MOV ESP, EBP
		POP EBP
		RETN
	}

}

namespace hooks {

void injectHarvestResource() {
	jmpPatch(transferResourceToWorkerWrapper, 0x004696D0, 0);
}


} //hooks
