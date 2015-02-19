/// This header file contains the structures and functions that allow you to
/// change the maximum sight range limit in StarCraft.

/// To use, add the following code to the gameOn() function in hooks/game_hooks.cpp:
///    setMaxSightRange<20>();  //Sets maximum sight range to 20

#pragma once
#include "../definitions.h"
#include "../hook_tools.h"
#pragma pack(1)

namespace offsets {
  const u32 SightStructArrayRef   = 0x00480709; //The pointer to the SightStruct array must be injected here
  const u32 InitializeSightValues = 0x0042AD60; //The internal function responsible for setting up the array
}

struct SightStruct {
  u32 tileSightWidth;
  u32 tileSightHeight;
  u32 unknown1;
  u32 unknown2;
  u32 unknown3;
  u32 unknown4;
  u32 unknown5;
};

C_ASSERT(sizeof(SightStruct) == 28);
//static_assert(sizeof(SightStruct) == 28, "The size of the SightStruct structure is invalid");

//Sight range varies between 0 and MAX_SIGHT_RANGE, inclusive
template <unsigned int MAX_SIGHT_RANGE>
void setMaxSightRange() {
  static SightStruct sightData[MAX_SIGHT_RANGE + 1] = {};

  for (unsigned int x = 0; x <= MAX_SIGHT_RANGE; ++x) {
    sightData[x].tileSightWidth   = x * 2 + 3;
    sightData[x].tileSightHeight  = x * 2 + 3;
    sightData[x].unknown1 = 3;
    sightData[x].unknown2 = 3;
  }

  memoryPatch(offsets::SightStructArrayRef, &sightData);

  const u16 mapTileWidth = mapTileSize->width;
  const u32 sightRangeParam = MAX_SIGHT_RANGE + 1;
  __asm {
    PUSHAD
    MOVZX EAX, mapTileWidth
    PUSH EAX
    MOV EAX, sightRangeParam
    LEA ECX, sightData
    CALL [offsets::InitializeSightValues]
    POPAD
  }
}

#pragma pack()
