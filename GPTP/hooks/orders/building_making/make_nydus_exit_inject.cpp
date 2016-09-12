#include "make_nydus_exit.h"
#include <hook_tools.h>

namespace {

	void __declspec(naked) orders_Build5Wrapper() {

		static CUnit* nydus_canal;

		__asm {
			PUSH EBP
			MOV EBP, ESP
			MOV nydus_canal, EBX
			PUSHAD
		}

		hooks::orders_Build5(nydus_canal);

		__asm {
			POPAD
			MOV ESP, EBP
			POP EBP
			RETN
		}

	}

	;

}; //unnamed namespace

namespace hooks {

	void injectMakeNydusExitHook() {
		jmpPatch(orders_Build5Wrapper,		0x0045DC20, 2);
	}

}; //hooks