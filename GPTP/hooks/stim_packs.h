#pragma once
#include "../SCBW/structures/CUnit.h"

//V241 for VS2008

namespace hooks {

void CMDACT_Stimpack();					//004234D0
void useStimPacksAIHook(CUnit* unit);	//004554A0
void CMDRECV_StimPack();				//004C2F30

void injectStimPacksHooks();

} //hooks
