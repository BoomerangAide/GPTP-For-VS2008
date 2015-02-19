// Contains the definitions of various data structures, arrays, pointers and
// internal constants in StarCraft.exe.
// The contents of this file are merged from: unit.cpp, triggers.cpp,
// resources.cpp, player.cpp, locations.cpp, buttons.cpp, and qdp.cpp.

//V241 for VS2008

#pragma once
#include "../definitions.h"
#include "structures.h"
#pragma pack(1)

#define SCBW_DATA(type, name, offset) type const name = (type)offset;

/// @name Linked list nodes
//////////////////////////////////////////////////////////////// @{

/// The first nodes in StarCraft's internal linked lists (taken from BWAPI's Offsets.h)
SCBW_DATA(CUnit**,      firstVisibleUnit,       0x00628430);
/// Includes units in transports/bunkers, workers inside gas buildings, nukes in
/// silos, queens inside command centers, and units in production.
SCBW_DATA(CUnit**,      firstHiddenUnit,        0x006283EC);
SCBW_DATA(CUnit**,      firstScannerSweep,      0x006283F4);
SCBW_DATA(CUnit**,      firstPsiFieldProvider,  0x0063FF54);
SCBW_DATA(CBullet**,    firstBullet,            0x0064DEC4);

struct Units12 { CUnit* unit[PLAYER_COUNT]; };
SCBW_DATA(Units12*,     firstPlayerUnit,        0x006283F8);  //Indexed by player Id

//////////////////////////////////////////////////////////////// @}

/// @name Structure tables
//////////////////////////////////////////////////////////////// @{

SCBW_DATA(CUnit*,       unitTable,    0x0059CCA8);
SCBW_DATA(CBullet*,     bulletTable,  0x0064B2E8);
SCBW_DATA(UNITDEATHS*,  deathTable,   0x0058A364);
SCBW_DATA(UNITDEATHS*,  unit_deaths,  deathTable);
SCBW_DATA(CSprite*,     spriteTable,  0x00629D98);

//From locations.cpp
SCBW_DATA(const MapSize*, mapTileSize,    0x0057F1D4);
SCBW_DATA(LOCATION*,      locationTable,  0x0058DC60);

//From buttons.cpp
BUTTON*     const button          = 0;  //???
BUTTON_SET* const buttonSet       = 0;  //???

SCBW_DATA(ActionPointer*, actionTable,    0x00512800);  //From triggers.cpp

//This was in the InitializePlugin() code in qdp.cpp.
//Not sure what this does, so I'm leaving it as a comment.
//actionTable[59] = &EnableDebugModeAction;

//////////////////////////////////////////////////////////////// @}

/// @name Data Variables and Constants
//////////////////////////////////////////////////////////////// @{

//From resources.cpp
struct Resources {
  int minerals[12];
  int gas[12];
  int cumulativeGas[12];
  int cumulativeMinerals[12];
};
SCBW_DATA(Resources*,     resources,      0x0057F0F0);

/// TBL files
SCBW_DATA(const StringTbl*, statTxtTbl,         0x006D1238);
SCBW_DATA(const StringTbl*, mapStringTbl,       0x005993D4);

/// Units that are selected by the current player (or the player viewing the replay).
SCBW_DATA(const Units12*, clientSelectionGroup, 0x00597208);
SCBW_DATA(const u8*,    clientSelectionCount,   0x0059723D);

/// Screen position relative to the map
SCBW_DATA(s32*,         screenX,                0x00628448);
SCBW_DATA(s32*,         screenY,                0x00628470);

/// Mouse position relative to the screen
SCBW_DATA(const Point32*, mouse,                0x006CDDC4);

/// Contains various information (names, player types, race types, and associated forces) of each player in the current game
SCBW_DATA(const PLAYER*,  playerTable,          0x0057EEE0);

struct SupplyData {
  u32 provided[PLAYER_COUNT];
  u32 used[PLAYER_COUNT];
  u32 max[PLAYER_COUNT];
};
SCBW_DATA(SupplyData*,    raceSupply,           0x00582144);  //Array; Use CUnit::getRace() to get the index.

SCBW_DATA(const u32*,     elapsedTimeFrames,    0x0057F23C);  //Elapsed game time in frames
SCBW_DATA(const u32*,     elapsedTimeSeconds,   0x0058D6F8);  //Elapsed game time in seconds
SCBW_DATA(const u8*,      GAME_TYPE,            0x00596820);  //Part of a larger structure; Compare with GameType::Enum.
SCBW_DATA(const s32*,     ACTIVE_NATION_ID,     0x00512678);  //AKA g_ActiveNationID
SCBW_DATA(const s32*,     LOCAL_NATION_ID,      0x00512684);  //AKA g_LocalNationID; Actually stores the player ID.
SCBW_DATA(const s32*,     LOCAL_HUMAN_ID,       0x00512688);  //AKA g_LocalHumanID; Invalid in replay games.
SCBW_DATA(const u8*,      CURRENT_TILESET,      0x00596828);  //Tileset of current map. Compare with TilesetType::Enum
////possible values were 0057F1DC and [00596828]

//////////////////////////////////////////////////////////////// @}

/// @name *.DAT File Data
//////////////////////////////////////////////////////////////// @{

// The following code is based on BWAPI's BW/Offsets.h
// you can get the other addresses in http://code.google.com/p/bwapi/source/browse/trunk/bwapi/BWAPI/Source/BW/Offsets.h
// Since StarCraft is already running when the plugin is loaded, the DatLoad
// structs are guaranteed to have the corrent offsets.

struct DatLoad {
  u32 address;
  u32 length;
  u32 entries;
};

namespace units_dat {
SCBW_DATA(const DatLoad*, unitsDat, 0x00513C30);

SCBW_DATA(u8*,  Graphic,            unitsDat[0].address);
SCBW_DATA(u16*, SubUnit,            unitsDat[1].address);
SCBW_DATA(u32*, ConstructionGraphic,  unitsDat[4].address);
SCBW_DATA(u8*,  ShieldsEnabled,     unitsDat[6].address);
SCBW_DATA(u16*, MaxShieldPoints,    unitsDat[7].address);
SCBW_DATA(s32*, MaxHitPoints,       unitsDat[8].address);
SCBW_DATA(u8*,  Elevation,          unitsDat[9].address);
SCBW_DATA(u8*,  MovementFlags,      unitsDat[10].address);
SCBW_DATA(u8*,  Rank,               unitsDat[11].address);
SCBW_DATA(u8*,  ComputerIdleOrder,  unitsDat[12].address);
SCBW_DATA(u8*,  HumanIdleOrder,     unitsDat[13].address);
SCBW_DATA(u8*,  ReturnToIdleOrder,  unitsDat[14].address);
SCBW_DATA(u8*,  AttackUnitOrder,    unitsDat[15].address);
SCBW_DATA(u8*,  AttackMoveOrder,    unitsDat[16].address);
SCBW_DATA(u8*,  GroundWeapon,       unitsDat[17].address);
SCBW_DATA(u8*,  MaxGroundHits,      unitsDat[18].address);
SCBW_DATA(u8*,  AirWeapon,          unitsDat[19].address);
SCBW_DATA(u8*,  MaxAirHits,         unitsDat[20].address);
SCBW_DATA(u32*, BaseProperty,       unitsDat[22].address);  // AKA SpecialAbilityFlags, UnitProperty, etc. Use with UnitProperty::Enum.
SCBW_DATA(u8*,  SeekRange,          unitsDat[23].address);  // AKA Target Acquisition Range, Acquire Target Range, etc.
SCBW_DATA(u8*,  SightRange,         unitsDat[24].address);
SCBW_DATA(u8*,  ArmorUpgrade,       unitsDat[25].address);
SCBW_DATA(u8*,  SizeType,           unitsDat[26].address);
SCBW_DATA(u8*,  ArmorAmount,        unitsDat[27].address);
SCBW_DATA(Box16*, UnitBounds,       unitsDat[38].address);
SCBW_DATA(u16*, MineralCost,        unitsDat[40].address);
SCBW_DATA(u16*, GasCost,            unitsDat[41].address);
SCBW_DATA(u16*, TimeCost,           unitsDat[42].address);
SCBW_DATA(GroupFlag*, GroupFlags,   unitsDat[44].address);
SCBW_DATA(u8*,  SupplyProvided,     unitsDat[45].address);  // Supply shown in-game is (true supply) / 2; e.g. Zerglings have 1 true supply, Marines have 2 true supply, etc.
SCBW_DATA(u8*,  SupplyRequired,     unitsDat[46].address);  // Supply shown in-game is (true supply) / 2; e.g. Zerglings have 1 true supply, Marines have 2 true supply, etc.
SCBW_DATA(u8*,  SpaceRequired,      unitsDat[47].address);
SCBW_DATA(u8*,  SpaceProvided,      unitsDat[48].address);
SCBW_DATA(u16*, BuildScore,         unitsDat[49].address);
SCBW_DATA(u16*, DestroyScore,       unitsDat[50].address);
SCBW_DATA(u16*, MapStringId,        unitsDat[51].address);
SCBW_DATA(u8*,  BroodwarOnly,       unitsDat[52].address);
} //units_dat

namespace flingy_dat {
SCBW_DATA(const DatLoad*, flingyDat, 0x00515A38);

SCBW_DATA(u16*, SpriteID,           flingyDat[0].address);
SCBW_DATA(u32*, TopSpeed,           flingyDat[1].address);
SCBW_DATA(u16*, Acceleration,       flingyDat[2].address);
SCBW_DATA(u32*, HaltDistance,       flingyDat[3].address);
SCBW_DATA(u8*,  TurnSpeed,          flingyDat[4].address);  //Incorrectly known as "Turn Radius"
SCBW_DATA(u8*,  MovementControl,    flingyDat[6].address);
} //flingy_dat

namespace weapons_dat {
SCBW_DATA(const DatLoad*, weaponsDat, 0x00513868);

SCBW_DATA(u16*, Label,              weaponsDat[0].address);
SCBW_DATA(u32*, FlingyId,           weaponsDat[1].address);
SCBW_DATA(TargetFlag*, TargetFlags, weaponsDat[3].address);
SCBW_DATA(u32*, MinRange,           weaponsDat[4].address);
SCBW_DATA(u32*, MaxRange,           weaponsDat[5].address);
SCBW_DATA(u8*,  DamageUpgrade,      weaponsDat[6].address);
SCBW_DATA(u8*,  DamageType,         weaponsDat[7].address); //Normal, Explosive, etc.. Use with DamageType::Enum.
SCBW_DATA(u8*,  Behavior,           weaponsDat[8].address); //Fly and follow target, appear on target unit, etc. Use with WeaponBehavior::Enum.
SCBW_DATA(u8*,  RemoveAfter,        weaponsDat[9].address);
SCBW_DATA(u8*,  ExplosionType,      weaponsDat[10].address);  //NormalHit, RadialSplash, EnemySplash, etc. Use with WeaponEffect::Enum.
SCBW_DATA(u16*, InnerSplashRadius,  weaponsDat[11].address);
SCBW_DATA(u16*, MediumSplashRadius, weaponsDat[12].address);
SCBW_DATA(u16*, OuterSplashRadius,  weaponsDat[13].address);
SCBW_DATA(u16*, DamageAmount,       weaponsDat[14].address);
SCBW_DATA(u16*, DamageBonus,        weaponsDat[15].address);
SCBW_DATA(u8*,  Cooldown,           weaponsDat[16].address);
SCBW_DATA(u8*,  DamageFactor,       weaponsDat[17].address);
SCBW_DATA(u8*,  AttackAngle,        weaponsDat[18].address);
SCBW_DATA(u8*,  LaunchSpin,         weaponsDat[19].address);
SCBW_DATA(u8*,  ForwardOffset,      weaponsDat[20].address);
SCBW_DATA(u8*,  VerticalOffset,     weaponsDat[21].address);
} //weapons_dat

namespace upgrades_dat {
SCBW_DATA(const DatLoad*, upgradesDat, 0x005136E0);

SCBW_DATA(u16*, MineralCostBase,    upgradesDat[0].address);
SCBW_DATA(u16*, MineralCostFactor,  upgradesDat[1].address);
SCBW_DATA(u16*, GasCostBase,        upgradesDat[2].address);
SCBW_DATA(u16*, GasCostFactor,      upgradesDat[3].address);
SCBW_DATA(u16*, TimeCostBase,       upgradesDat[4].address);
SCBW_DATA(u16*, TimeCostFactor,     upgradesDat[5].address);
SCBW_DATA(u16*, Label,              upgradesDat[8].address);
SCBW_DATA(u8*,  Race,               upgradesDat[9].address);
SCBW_DATA(u8*,  MaxRepeats,         upgradesDat[10].address);
} //upgrades_dat

namespace techdata_dat {
SCBW_DATA(const DatLoad*, techdataDat, 0x005137D8);

SCBW_DATA(u16*, MineralCost,        techdataDat[0].address);
SCBW_DATA(u16*, GasCost,            techdataDat[1].address);
SCBW_DATA(u16*, TimeCost,           techdataDat[2].address);
SCBW_DATA(u16*, EnergyCost,         techdataDat[3].address);
SCBW_DATA(u16*, Label,              techdataDat[7].address);
} //techdata_dat

namespace orders_dat {
SCBW_DATA(const DatLoad*, ordersDat, 0x00513EC8);

SCBW_DATA(u16*, Label,              ordersDat[0].address);
SCBW_DATA(u8*,  UseWeaponTargeting, ordersDat[1].address);
SCBW_DATA(u8*,  TechUsed,           ordersDat[14].address);
} //orders_dat

namespace sprites_dat {
SCBW_DATA(const DatLoad*, spritesDat, 0x00513FB8);

SCBW_DATA(u16*, ImageId,            spritesDat[0].address);
SCBW_DATA(s8*,  HpBarSize,          spritesDat[1].address);
SCBW_DATA(u8*,  IsVisible,          spritesDat[3].address);
} //sprites_dat

namespace images_dat {
SCBW_DATA(const DatLoad*, imagesDat, 0x00514010);

SCBW_DATA(const u8*,  IsTurnable,   imagesDat[1].address);
SCBW_DATA(const u8*,  IsClickable,  imagesDat[2].address);
SCBW_DATA(const u8*,  RLE_Function, imagesDat[5].address);
SCBW_DATA(const u8*,  Remapping,    imagesDat[6].address);
} //images_dat


//////////////////////////////////////////////////////////////// @}

/// @name Reserved data
/// Warning: The following section contains data reserved for internal use only.
///          If you are a modder, use these at your own risk!
//////////////////////////////////////////////////////////////// @{

//Helper functions for several hooks
SCBW_DATA(u8*,          selectionIndexStart,    0x006284B6);
typedef CUnit* (__cdecl *GetActivePlayerNextSelectionFunc)();
SCBW_DATA(GetActivePlayerNextSelectionFunc, getActivePlayerNextSelection, 0x0049A850);

typedef void (__fastcall *PrepareForNextOrderFunc)(CUnit*);
SCBW_DATA(PrepareForNextOrderFunc, prepareForNextOrder, 0x00475000);

//Contains various info on the tiles.
SCBW_DATA(ActiveTile**, activeTileArray,        0x006D1260);

// Stores an ordered list of all units currently in the game.
SCBW_DATA(UnitFinderData*, unitOrderingX,       0x0066FF78);
SCBW_DATA(UnitFinderData*, unitOrderingY,       0x006769B8);
SCBW_DATA(const u32*,   unitOrderingCount,      0x0066FF74);

SCBW_DATA(const Point32*, angleDistance,        0x00512D28);

// Font & Drawing
namespace graphics { class Font; class Bitmap; }
SCBW_DATA(graphics::Font**, fontBase,           0x006CE0F4);
SCBW_DATA(graphics::Bitmap*, gameScreenBuffer,  0x006CEFF0);
SCBW_DATA(u8*,          refreshRegions,         0x006CEFF8);  //640 x 480 divided into 1200 squares of 16x16
SCBW_DATA(Layers*,      screenLayers,           0x006CEF50);
typedef void (__stdcall *DrawGameProc)(graphics::Bitmap *surface, Bounds *bounds);
static DrawGameProc const oldDrawGameProc = (DrawGameProc) 0x004BD580;
SCBW_DATA(int*,          colorReordering,		0x0057F21C);	//array used in multiplayer to randomize colors
																//used by unit.getColor() and player.getColor()

const CListExtern<CImage, &CImage::link> unusedImages(0x0057EB68, 0x0057EB70);
SCBW_DATA(CList<CSprite>*, unusedSprites,       0x0063FE30);

struct SpriteTileData {
  CSprite* tails[256];
  CSprite* heads[256];
};
SCBW_DATA(SpriteTileData*, spritesOnTileRow,    0x00629288);

//Image-related
struct ImagesDatExtraOverlayLO_Files {
  LO_Header* attackOverlays[IMAGE_TYPE_COUNT];
  LO_Header* damageOverlays[IMAGE_TYPE_COUNT];
  LO_Header* specialOverlays[IMAGE_TYPE_COUNT];
  LO_Header* landingDustOverlays[IMAGE_TYPE_COUNT];
  LO_Header* liftoffDustOverlays[IMAGE_TYPE_COUNT];
};
SCBW_DATA(const ImagesDatExtraOverlayLO_Files*, lo_files, 0x0051F2A8);
SCBW_DATA(const LO_Header* const*, shieldOverlays, 0x0052E5C8);

SCBW_DATA(const ColorShiftData*, colorShift, 0x005128F8); //Use ColorRemapping::Enum as index
SCBW_DATA(GrpHead* const*, imageGrpGraphics, 0x0051CED0);

template <typename T>
struct PlayerFlags {
  T flags[PLAYER_COUNT];
};
SCBW_DATA(PlayerFlags<u8>*, playerAlliance,     0x0058D634);  //See scbw::isAlliedTo()
SCBW_DATA(PlayerFlags<u32>*, playerVision,      0x0057F1EC);

SCBW_DATA(CUnit* const*,  activePortraitUnit,   0x00597248);

SCBW_DATA(AI_Main*,       AIScriptController,   0x0068FEE8);
SCBW_DATA(AiCaptain* const*, AiRegionCaptains,  0x0069A604);
SCBW_DATA(u32*,           aiSupplyReserved,     0x006CA4BC);

//-------- Internal constants --------//

SCBW_DATA(const Bool32*,  IS_GAME_PAUSED,       0x006509C4);  //See scbw::isGamePaused()
SCBW_DATA(const Bool8*,   IS_BROOD_WAR,         0x0058F440);  //See scbw::isBroodWarMode()
SCBW_DATA(const u32*,     CHEAT_STATE,          0x006D5A6C);  //See scbw::isCheatEnabled()
SCBW_DATA(const s32*,     MAX_UNIT_WIDTH,       0x006BEE68);
SCBW_DATA(const s32*,     MAX_UNIT_HEIGHT,      0x006BB930);
SCBW_DATA(const Bool32*,  IS_IN_REPLAY,         0x006D0F14);  //See scbw::isInReplay()
SCBW_DATA(Bool32*,        IS_IN_GAME_LOOP,      0x006D11C8);
SCBW_DATA(u32*,           lastRandomNumber,     0x0051CA14);  //See scbw::random(), scbw::randBetween()
SCBW_DATA(Bool32*,        canUpdatePoweredStatus, 0x0063FF44);
SCBW_DATA(const Bool32*,  IS_PLACING_BUILDING,  0x00640880);

//-------- Tech levels --------//

struct _scTechs {
  u8 isEnabled[PLAYER_COUNT][24];
  u8 isResearched[PLAYER_COUNT][24];
};
struct _bwTechs {
  u8 isEnabled[PLAYER_COUNT][20];
  u8 isResearched[PLAYER_COUNT][20];
};
SCBW_DATA(_scTechs*, TechSc,   0x0058CE24); //Use with ScTech::Enum
SCBW_DATA(_bwTechs*, TechBw,   0x0058F050); //Use with BwTech::Enum

//-------- Upgrade levels --------//

struct _scUpgrs {
  u8 maxLevel[PLAYER_COUNT][46];
  u8 currentLevel[PLAYER_COUNT][46];
};
struct _bwUpgrs {
  u8 maxLevel[PLAYER_COUNT][15];
  u8 currentLevel[PLAYER_COUNT][15];
};
SCBW_DATA(_scUpgrs*, UpgradesSc,  0x0058D088); //Use with ScUpgrade::Enum
SCBW_DATA(_bwUpgrs*, UpgradesBw,  0x0058F278); //Use with BwUpgrade::Enum

//////////////////////////////////////////////////////////////// @}

#undef SCBW_DATA
#pragma pack()