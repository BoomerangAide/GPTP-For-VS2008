#pragma once
#include "../../definitions.h"
#include "../../hook_tools.h"
#pragma pack(1)

//To use, change the following constant and
//make sure the injection function is in
//initialize.cpp and enabled.
//You may need to use hooks\unit_stats\sight_range
//to handle sight range upgrades or to create cases
//to have a spellcasting range different from sight
//range.
#define CUSTOM_MAX_SIGHT_RANGE 11

//The sight range is used as a byte so it cannot
//be higher than 255, and sight values above 138
//were shown (through testing) to crash the game too.
C_ASSERT(CUSTOM_MAX_SIGHT_RANGE <= 138);

struct SightStruct {
/*00*/	u32 tileSightWidth;
/*04*/	u32 tileSightHeight;
/*08*/	u32 unknown1;	//value is 3
/*0C*/	u32 unknown2;	//value is 3
/*10*/	u32 unknown3;	//value is unk1*unk2 so 9
/*14*/	u32 unknown4;
/*18*/	u32 unknown5;	//pointer on dynamically allocated memory
};

C_ASSERT(sizeof(SightStruct) == 28);	//0x1C

//Original array was in 0x00513A18
SightStruct sightData[CUSTOM_MAX_SIGHT_RANGE + 1] = {};

//Sight range varies between 0 and MAX_SIGHT_RANGE, inclusive
void initMaxSightRangeArray() {

	for (unsigned int x = 0; x <= CUSTOM_MAX_SIGHT_RANGE; x++) {
		sightData[x].tileSightWidth	 = x * 2 + 3;
		sightData[x].tileSightHeight	= x * 2 + 3;
		sightData[x].unknown1 = 3;
		sightData[x].unknown2 = 3;
	}

}

namespace hooks {

void injectExtendSightLimitMod() {

	//crashing point
	//StarCraft.exe+802F6- mov edx,[ebx+eax*4]

	initMaxSightRangeArray();

	//allow sightData to be used properly
	memoryPatch(0x00480709, &sightData);

	//allow sightData to be initialized properly
	memoryPatch(0x0048098B, (int)(CUSTOM_MAX_SIGHT_RANGE + 1));
	memoryPatch(0x00480990, &sightData);

	//allow sightData dynamically allocated memory to be deleted properly
	memoryPatch(0x00480354, &(sightData[0].unknown5));
	memoryPatch(0x00480359, (int)(CUSTOM_MAX_SIGHT_RANGE + 1));

}

};

#pragma pack()
