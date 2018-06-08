#pragma once
#include "../../SCBW/structures/CUnit.h"
#include "../../SCBW/structures.h"

namespace hooks {

	void stats_panel_display(BinDlg* dialog);	//00426C60

	void injectStatsPanelDisplayHook();

}