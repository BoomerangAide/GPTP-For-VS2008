#include "buttonsets.h"
#include <hook_tools.h>

namespace {

//Originally 00458BC0  updateButtonSetEx
const u32 Func_UpdateButtonSetEx = 0x00458BC0;
void __declspec(naked) updateButtonSetExWrapper() {

	__asm {
		PUSHAD
		MOV EBP, ESP
	}

	hooks::updateButtonSetEx();

	__asm {
		POPAD
		RET
	}

}

//Originally 00458D50  sub_458D50
const u32 Func_Sub_458D50 = 0x00458D50;
void __declspec(naked) updateButtonSet_Sub458D50Wrapper() {

	__asm PUSHAD

	hooks::updateButtonSet_Sub458D50();

	__asm {
		POPAD
		RET
	}

}

//Originally 00458DE0  updateButtonSet
const u32 Func_UpdateButtonSet = 0x00458DE0;
void __declspec(naked) updateButtonSetWrapper() {

	__asm PUSHAD

	if(hooks::updateButtonSet()) {
		__asm {
			POPAD
			JMP Func_UpdateButtonSetEx
		}
	}
	else
		__asm {
			POPAD
			RET
		}

}

//Modify offset 004591ED to use the custom
//getButtonSet function
//Don't replace the entire function
const u32 Func_Sub_4591D0 = 0x004591ED;
const u32 Patch_For_Sub4591D0_Back = 0x004591F4;
void __declspec(naked) getButtonSetPatch_For_Sub4591D0() {

	static u32 index;
	static BUTTON_SET* returnValue;

	__asm {
		MOV index, ECX
		PUSHFD
		PUSHAD
	}

	//In assembly, the index get multiplied to fit
	//the size of the variable to get, which is
	//why the value must get divided here.

	returnValue = hooks::getButtonSet(index/3);

	__asm {
		POPAD
		POPFD
		MOV ECX, returnValue
		PUSH Patch_For_Sub4591D0_Back
		RET 
	}

}

} //unnamed namespace

namespace hooks {

void injectButtonSetHooks() {
  jmpPatch(updateButtonSetExWrapper,			Func_UpdateButtonSetEx, 1);
  jmpPatch(updateButtonSet_Sub458D50Wrapper,	Func_Sub_458D50, 2);
  jmpPatch(updateButtonSetWrapper,				Func_UpdateButtonSet);
  jmpPatch(getButtonSetPatch_For_Sub4591D0,		Func_Sub_4591D0, 1);
}

} //hooks
