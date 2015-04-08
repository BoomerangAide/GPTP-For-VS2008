//All-in-one include file
//Structs by poiuy_qwert, A_of_s_t, ravenwolf and pastelmind.
//Special thanks to Heinermann
//V241 for VS2008

#pragma once

const int PLAYER_COUNT			    = 12;
const int PLAYABLE_PLAYER_COUNT = 8;
const int UNIT_ARRAY_LENGTH		  = 1700;
const int BULLET_ARRAY_LENGTH	  = 100;
const int SPRITE_ARRAY_LENGTH	  = 2500;
const int UNIT_TYPE_COUNT		    = 228;
const int TECH_TYPE_COUNT		    = 44;
const int UPGRADE_TYPE_COUNT	  = 61;
const int WEAPON_TYPE_COUNT		  = 130;
const int FLINGY_TYPE_COUNT		  = 209;
const int IMAGE_TYPE_COUNT		  = 999;

#include "structures/CUnit.h"
#include "structures/CBullet.h"
#include "structures/CSprite.h"
#include "structures/CImage.h"
#include "structures/COrder.h"
#include "structures/Layer.h"
#include "structures/Player.h" //made into external file to have .cpp

#pragma pack(1)

struct UNITDEATHS {
  u32        player[12];
};

//Based on http://code.google.com/p/bwapi/source/browse/branches/bwapi4/bwapi/BWAPI/Source/BW/CImage.h

struct TEXT {
  char  textdisplay[218][13];  //[last is text at bottom; ex: "Cheat enabled."]
  UNK   unknown1;
  UNK   unknown2;
  u8    color[13];
  UNK   unknown3[3];  //[last is text at bottom; ex: "Cheat enabled."]
  u8    timer[13];
};

struct TILE {
  u16 index;
  u8 buildability; /**< 8th bit should sign not buildable. */
  u8 groundHeight; /**< Ground Height(4 lower bits) - Deprecated? Some values are incorrect. */
  u16 leftEdge;
  u16 topEdge;
  u16 rightEdge;
  u16 buttomEdge;
  u16 _1;
  u16 _2; /**<  Unknown - Edge piece has rows above it. (Recently noticed; not fully understood.)
                o 1 = Basic edge piece.
                o 2 = Right edge piece.
                o 3 = Left edge piece.*/
  u16 _3;
  u16 _4;
  u16 miniTile[16]; /** MegaTile References (VF4/VX4) */
};

struct DOODAD {
  u16 index;
  u8 buildability; /**< 8th bit should sign not buildable. */
  u8 groundHeightAndOverlayFlags; /**< Ground Height(4 lower bits) - Deprecated? Some values are incorrect.
                   * Overlay Flags:
                   * o 0x0 - None
                   * o 0x1 - Sprites.dat Reference
                   * o 0x2 - Units.dat Reference (unit sprite)
                   * o 0x4 - Overlay is Flipped
                   */
  u16 overlayID;
  u16 _1;
  u16 doodatGrupString;
  u16 _2;
  u16 dddataBinIndex;
  u16 doodatHeight;
  u16 doodatWidth;
  u16 _3;
  u16 miniTile[16]; /** MegaTile References (VF4/VX4) */
};

struct CThingy {
  CThingy *prev;
  CThingy *next;
  u32     unitType;
  CSprite *sprite;
};

//---- Taken from locations.cpp ----//

struct MapSize {
  u16   width;
  u16   height;
};

struct LOCATION {
  Box32 dimensions;
  u16   stringId;
  u16   flags;
};

//---- Taken from buttons.cpp ----//

typedef u32 ButtonState;
typedef ButtonState (__fastcall *REQ_FUNC)(u32, u32, CUnit*);
//(u32 reqVar, u32 playerId, CUnit* selected);
typedef void (__fastcall *ACT_FUNC)(u32,u32);
//(u32 actVar, u32 shiftClick);

struct BUTTON {
  u16       position;
  u16       iconID;
  REQ_FUNC  *reqFunc;
  ACT_FUNC  *actFunc;
  u16       reqVar;
  u16       actVar;
  u16       reqStringID;
  u16       actStringID;
};

struct BUTTON_SET {
  u32     buttonsInSet;
  BUTTON  *firstButton;
  u32     connectedUnit;
};

//---- Taken from triggers.h ----//
struct CONDITION {
  u32        location;
  u32        player;
  u32        number;
  u16        unit;
  u8        comparison;
  u8        condition;
  u8        type;
  u8        flags;
};

typedef Bool32 (__fastcall *ConditionPointer)(CONDITION*);

struct ACTION {
  u32        location;
  u32        string;
  u32        wavString;
  u32        time;
  u32        player;
  u32        number;
  u16        unit;
  u8        action;
  u8        number2;
  u8        flags;
};

typedef Bool32 (__fastcall *ActionPointer)(ACTION*);

//GRP frame header
struct GrpFrame {
  s8  x;
  s8  y;
  s8  width;
  s8  height;
  u32 dataOffset;
};

C_ASSERT(sizeof(GrpFrame) == 8); 
//static_assert(sizeof(GrpFrame) == 8, "The size of the GrpFrame structure is invalid");

//GRP file header
struct GrpHead {
  u16 frameCount;
  s16 width;
  s16 height;
  GrpFrame frames[1];
};

C_ASSERT(sizeof(GrpHead) == 14); 
//static_assert(sizeof(GrpHead) == 14, "The size of the GrpHead structure is invalid");

//LO* file header
struct LO_Header {
  u32 frameCount;
  u32 overlayCount;
  u32 frameOffsets[1];

  Point8 getOffset(int frameNum, int overlayNum) const {
    return ((Point8*)(this->frameOffsets[frameNum] + (u32)this))[overlayNum];
  }
};

C_ASSERT(sizeof(LO_Header) == 12);
//static_assert(sizeof(LO_Header) == 12, "The size of the LO_Header structure is invalid");


//Image Remapping Data
struct ColorShiftData {
  u32 index;
  void* data;
  char name[12];
};

C_ASSERT(sizeof(ColorShiftData) == 20);
//static_assert(sizeof(ColorShiftData) == 20, "The size of the ColorShiftData structure is invalid");

//-------- Flag structures --------//

//Based on BWAPI's Offsets.h
struct ActiveTile {
  u8 visibilityFlags;
  u8 exploredFlags;
  u8 isWalkable         : 1; // Set on tiles that can be walked on
  u8 unknown1           : 1; // Unused?
  u8 isUnwalkable       : 1; // Set on tiles that can't be walked on
  u8 unknown2           : 1; // Unused?
  u8 hasDoodadCover     : 1; // Set when a doodad cover (trees) occupies the area
  u8 unknown3           : 1; // Unused?
  u8 hasCreep           : 1; // Set when creep occupies the area
  u8 alwaysUnbuildable  : 1; // always unbuildable, like water
  u8 groundHeight       : 3; // ground height; 1 for low ground, 2 for middle ground and 4 for high ground
  u8 currentlyOccupied  : 1; // unbuildable but can be made buildable
  u8 creepReceeding     : 1; // Set when the nearby structure supporting the creep is destroyed
  u8 cliffEdge          : 1; // Set if the tile is a cliff edge
  u8 temporaryCreep     : 1; // Set when the creep occupying the area was created. Not set if creep tiles were preplaced. Used in drawing routine.
  u8 unknown4           : 1; // Unused?
};

C_ASSERT(sizeof(ActiveTile) == 4);
//static_assert(sizeof(ActiveTile) == 4, "The size of the ActiveTile structure is invalid");

struct GroupFlag {
  u8 isZerg         : 1;
  u8 isTerran       : 1;
  u8 isProtoss      : 1;
  u8 isMen          : 1;
  u8 isBuilding     : 1;
  u8 isFactory      : 1;
  u8 isIndependent  : 1;
  u8 isNeutral      : 1;
};

C_ASSERT(sizeof(GroupFlag) == 1);
//static_assert(sizeof(GroupFlag) == 1, "The size of the GroupFlag structure is invalid");

struct TargetFlag {
  u16 air         : 1;
  u16 ground      : 1;
  u16 mechanical  : 1;
  u16 organic     : 1;
  u16 nonBuilding : 1;
  u16 nonRobotic  : 1;
  u16 terrain     : 1;
  u16 orgOrMech   : 1;
  u16 playerOwned : 1;
};

C_ASSERT(sizeof(TargetFlag) == 2);
//static_assert(sizeof(TargetFlag) == 2, "The size of the TargetFlag structure is invalid");

//-------- End of flag structures --------//

struct UnitFinderData {
  s32 unitIndex;
  s32 position;
  bool operator < (const UnitFinderData& rhs) const {
    return this->position < rhs.position;
  }
};

C_ASSERT(sizeof(UnitFinderData) == 8);
//static_assert(sizeof(UnitFinderData) == 8, "The size of the UnitFinderData structure is invalid");

struct Bounds {
  u16 left;
  u16 top;
  u16 right;
  u16 bottom;
  u16 width;
  u16 height;
};

C_ASSERT(sizeof(Bounds) == 12);
//static_assert(sizeof(Bounds) == 12, "The size of the Bounds structure is invalid");

//BinDlg is defined in https://code.google.com/p/vgce/source/browse/trunk/docs/Blizzard/Starcraft/BIN%20FORMAT.txt
//as Dialog Structure

struct BinDlg {
/*0x00*/  BinDlg  *next;
/*0x04*/  Bounds  bounds;
/*0x10*/  u8      *buffer;
/*0x14*/  char    *pszText;
/*0x18*/  u32     flags;
/*0x1C*/  u32     unk_1c;
/*0x20*/  u16     index;
/*0x22*/  u16     controlType;
/*0x24*/  u16     graphic;
/*0x26*/  u32     *user;
/*0x2A*/  void    *fxnInteract;
/*0x2E*/  void    *fxnUpdate;
/*0x32*/  BinDlg  *parent;
/*0x36*/  Box16   responseArea;
/*0x3E*/  u32     unk_3e;
/*0x42*/  void    *childrenSmk;
/*0x46*/  Point16 textPos;
/*0x4A*/  u16     responseAreaWidth;
/*0x4C*/  u16     responseAreaHeight;
/*0x4E*/  UNK     unk_4e[8];
};

C_ASSERT(sizeof(BinDlg) == 86); 
//static_assert(sizeof(BinDlg) == 86, "The size of the BinDlg structure is invalid");

struct GuiOverlay {
  UNK     unk_0[6];
  u16     overlayType;
  u16     id;
  UNK     unk_a[34];
};

C_ASSERT(sizeof(GuiOverlay) == 44); 
//static_assert(sizeof(GuiOverlay) == 44, "The size of the GuiOverlay structure is invalid");

//-------- AI related stuff --------//

struct AI_Main {
  s32 oreCollection;
  s32 gasCollection;
  s32 supplyCollection;
  s32 ore;
  s32 gas;
  s32 supply;
  u8  unknown_0x18;
  u8  newBuildType;
  u16 nextBuildType;
  void  *pTownMain;
  u32 unknown_0x20[124];
  u8  unknown_0x210;
  u8  builtSomething;
  u8  AI_NukeRate;
  u8  AI_Attacks;
  u32 AI_LastNukeTime;
  struct {
    u16 isSecureFinished    : 1;
    u16 isTownStarted       : 1;
    u16 isDefaultBuildOff   : 1;
    u16 isTransportsOff     : 1;
    u16 isFarmsNotimingOn   : 1;
    u16 isUseMapSettings    : 1;
    u16 flag_0x40           : 1;
    u16 spreadCreep         : 1;
    u16 flag_0x100          : 1;
    u16 hasStrongestGndArmy : 1;  //Set if the AI's ground army is stronger than the total strength of the strongest enemy force
    u16 bUpgradesFinished   : 1;
    u16 bTargetExpansion    : 1;
  } AI_Flags;
  u16 AI_PanicBlock;
  u16 AI_MaxForce;
  u16 AI_AttackGroup;
  u16 waitForceCount;
  u8  AI_DefaultMin;
  u8  unknown_0x223;
  u32 lastIndividualUpdateTime;
  u32 AI_AttackTimer;
  u8  unknown_0x22C;
  u8  spellcasterTimer;
  u8  attackManagerTimer;
  u8  AI_IfDif;
  u16 AI_AttackGroups[64];
  u32 AI_DefenseBuild_GG[10];
  u32 AI_DefenseBuild_AG[10];
  u32 AI_DefenseBuild_GA[10];
  u32 AI_DefenseBuild_AA[10];
  u32 AI_DefenseUse_GG[10];
  u32 AI_DefenseUse_AG[10];
  u32 AI_DefenseUse_GA[10];
  u32 AI_DefenseUse_AA[10];
  u8  AI_DefineMax[UNIT_TYPE_COUNT];
  CUnit *mainMedic;
  Box32 genCmdLoc;
};

C_ASSERT(sizeof(AI_Main) == 1256); 
//static_assert(sizeof(AI_Main) == 1256, "The size of the AI_Main structure is invalid");

struct AiCaptain {
  u16 region;
  u16 unknown_0x2;
  u8  playerId;
  u8  captainType;
  u8  unknown_0x6;
  u8  unknown_0x7;
  u8  captainFlags;
  u8  unknown_0x9;
  u8  unknown_0xA;
  u8  unknown_0xB;
  u16 unknown_0xC;
  u16 unknown_0xE;
  u16 regionGndStrength;
  u16 regionAirStrength;
  u16 fullGndStrength;
  u16 fullAirStrength;
  u16 unknown_0x18;
  u16 unknown_0x1A;
  u32 unknown_0x1C;
  u32 unknown_0x20;
  CUnit *slowestUnit;
  CUnit *followTarget;
  CUnit *mainMedic;
  void  *town;
};

C_ASSERT(sizeof(AiCaptain) == 52); 
//static_assert(sizeof(AiCaptain) == 52, "The size of the AiCaptain structure is invalid");

/// From BWAPI Offsets.h, used in scbwdata.h by UnitAvailability
struct _uavail {
	u8 available[PLAYER_COUNT][UNIT_TYPE_COUNT];
};

class StringTbl {
  public:
    /// Returns the number of string entries in the TBL file.
    u16 getStringCount() const { return *buffer; }

    /// Returns the string at @p index in the TBL file.
    /// If the @p index is 0, returns NULL.
    /// If the @p index is out of bounds, returns an empty string.
    const char* getString(u16 index) const {
      //Based on function @ 0x004C36F0
      if (index == 0) return NULL;
      else if (index <= getStringCount())
        return (const char*)(buffer) + buffer[index];
      else
        return "";
    }

  private:
    u16* buffer;
};

#pragma pack()
