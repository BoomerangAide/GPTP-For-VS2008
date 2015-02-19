#include "harvest.h"
#include "../hook_tools.h"

void __declspec(naked) transferResourceToWorkerWrapper() {
  CUnit *worker, *resource;
  __asm {
    PUSHAD
    MOV EBP, ESP
    MOV worker, ECX
    MOV resource, EAX
  }

  hooks::transferResourceToWorkerHook(worker, resource);

  __asm {
    POPAD
    RETN
  }
}

namespace hooks {

void injectHarvestResource() {
  jmpPatch(transferResourceToWorkerWrapper, 0x004696D0);
}


} //hooks
