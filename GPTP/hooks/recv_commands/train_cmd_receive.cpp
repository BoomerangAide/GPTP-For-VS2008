#include "train_cmd_receive.h"
#include <SCBW/api.h>

//Helper functions declaration

namespace {

bool HasMoneyCanMake(CUnit* builder, u32 unitToBuild);	//67250

} //unnamed namespace

namespace hooks {

void CMDRECV_TrainFighter() {

	CUnit* current_selection;

	*selectionIndexStart = 0;
	current_selection = getActivePlayerNextSelection();

	while(current_selection != NULL) {

		u32 unitToBuild;

		//the original code was messy, simplified/optimized version here
		if(current_selection->id == UnitId::ProtossCarrier)
			unitToBuild = UnitId::ProtossInterceptor;
		else
		if(current_selection->id == UnitId::Hero_Gantrithor)
			unitToBuild = UnitId::ProtossInterceptor;
		else
		if(current_selection->id == UnitId::ProtossReaver)
			unitToBuild = UnitId::ProtossScarab;
		else
		if(current_selection->id == UnitId::Hero_Warbringer)
			unitToBuild = UnitId::ProtossScarab;
		else
			unitToBuild = 0; //not translating it as marine as it's an error case

		if(current_selection->canMakeUnit(unitToBuild,*ACTIVE_NATION_ID) == 1 &&
			HasMoneyCanMake(current_selection,unitToBuild) //add unit to build queue if successful
			) 
		{
			if(	current_selection->id == UnitId::ProtossCarrier ||
				current_selection->id == UnitId::Hero_Gantrithor ||
				current_selection->id == UnitId::ProtossReaver ||
				current_selection->id == UnitId::Hero_Warbringer
				)
			{

				if(current_selection->secondaryOrderState != 2) {
					current_selection->secondaryOrderId = OrderId::TrainFighter;
					current_selection->secondaryOrderPos.y = 0;
					current_selection->secondaryOrderPos.x = 0;
					current_selection->currentBuildUnit = NULL;
					current_selection->secondaryOrderState = 0;
				}

			}
		}

		current_selection = getActivePlayerNextSelection();

	}

	scbw::refreshConsole();

}

;

//Note: the default function isn't compatible with multiple selection
void CMDRECV_Train(u16 wUnitType) {

	CUnit* builder;

	*selectionIndexStart = 0;
	builder = getActivePlayerNextSelection();

	if(builder != NULL && getActivePlayerNextSelection() == NULL) {

		if(builder->canMakeUnit(wUnitType,*ACTIVE_NATION_ID) == 1 &&
			wUnitType <= UnitId::Spell_DisruptionWeb //id before buildings id
		)
		{
			if(HasMoneyCanMake(builder,wUnitType)) //add unit to build queue if successful
				builder->setSecondaryOrder(OrderId::Train);
			scbw::refreshConsole();
		}

	}

}

;

} //namespace hooks

//-------- Helper function definitions. Do NOT modify! --------//

namespace {

const u32 Func_HasMoneyCanMake = 0x00467250;
bool HasMoneyCanMake(CUnit* builder, u32 unitToBuild) {

	static Bool32 bPreResult;

	__asm {
		PUSHAD
		PUSH unitToBuild
		MOV EDI, builder
		CALL Func_HasMoneyCanMake
		MOV bPreResult, EAX
		POPAD
	}

	return (bPreResult != 0);

}

} //unnamed namespace

//End of helper functions
