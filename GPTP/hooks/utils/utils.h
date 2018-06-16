#pragma once
#include "../../SCBW/structures.h"

namespace hooks {

void InitializeDialog(BinDlg* dialog, void* dlgFunc);	//00419D20
bool unit_IsStandardAndMovable(CUnit* unit);			//0047B770
CUnit* getActivePlayerFirstSelection();					//0049A850

void injectUtilsHooks();

} //hooks
