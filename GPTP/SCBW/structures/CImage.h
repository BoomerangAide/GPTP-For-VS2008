//Based on BWAPI's BW/CBullet.h

#pragma once
#include "common.h"
#include "CList.h"
#include <SCBW/enumerations.h>
#pragma pack(1)

//V241 for VS2008
//Additions from bwapi/bwapi/BWMemoryEdit/Enums/RLE.cs
//Additions from bwapi/bwapi/BWAPI/Source/BW/CImage.h

struct CSprite;
struct GrpHead;
struct GrpFrame;

/// Used by CImage.paletteType
namespace PaletteType {
enum Enum : u8 {
	RLE_NORMAL = 0,
	RLE_1 = 1,
	RLE_2 = 2,
	RLE_3 = 3,
	RLE_4 = 4, 
	RLE_CLOAK = 5,
	RLE_CLOAKED = 6, 
	RLE_DECLOAK = 7,
	RLE_8 = 8, 
	RLE_EFFECT = 9,
	RLE_SHADOW = 10, 
	RLE_HPFLOATDRAW = 11,
	RLE_WARP = 12, 
	RLE_OUTLINE = 13,
	RLE_PLAYER_SIDE = 14, 
	RLE_15 = 15,
	RLE_SHIFT = 16, 
	RLE_FIRE = 17
};
}

//note: the flag number is chosen according to the value used in 
//<< flag operations, that's why it start with 0.
namespace CImage_Flags {
enum Enum : u16 {
	 Redraw				=	0x0001,				//flag 0   : 0x0001
	 Mirrored			=	0x0002,				//flag 1   : 0x0002
	 DontUpdate			=	0x0004,				//flag 2   : 0x0004
	 HasRotationFrames	=	0x0008,				//flag 3   : 0x0008
	 Flag04				=	0x0010,				//flag 4   : 0x0010
	 Clickable			=	0x0020,				//flag 5   : 0x0020
	 Invisible			=	0x0040,				//flag 6   : 0x0040 , hidden/invisible (don't draw)*/
	 Flag07				=	0x0080,				//flag 7   : 0x0080
	 Flag08				=	0x0100,				//flag 8   : 0x0100
	 Flag09				=	0x0200,				//flag 9   : 0x0200
	 Flag10				=	0x0400,				//flag 10  : 0x0400
	 Flag11				=	0x0800,				//flag 11  : 0x0800
	 Flag12				=	0x1000,				//flag 12  : 0x1000
	 Flag13				=	0x2000,				//flag 13  : 0x2000
	 Flag14				=	0x4000,				//flag 14  : 0x4000
	 Flag15				=	0x8000				//flag 15  : 0x8000
};
}

struct CImage {
//Utility method definitions added by pastelmind


  /// Makes the image play the specified Iscript animation entry.
  void playIscriptAnim(IscriptAnimation::Enum animation);

  /// AKA ImageDestructor() @ 0x004D4CE0
  /// Removes the image from the linked list of valid images. This is different
  /// from a class destructor, since CImage objects are stored in a static array
  /// and never truly destroyed.
  void free();

  /// Set the color remapping of this image to @ remapping.
  void setRemapping(ColorRemapping::Enum remapping);

  /// Resets most of the data member values. This is meant to be used in other
  /// functions, and should not be used by modders.
  void initializeData(CSprite *parent, u16 imageId, s8 x, s8 y);

  /// Return a pointer to the current frame when called
  GrpFrame* getCurrentFrame() const;

////////////////////////////////////////////////////////////////
//Actual data structure
  CLink<CImage> link;
  u16         id;


/// ++Drawing function (values are the same as DataEdit)
/// officially "ubRLE"
  u8						paletteType; //Use PaletteType::Enum
  u8						direction;		  
  u16						flags;		// Use CImage_Flags::enum
  u8						horizontalOffset;
  u8						verticalOffset;
  u16						iscriptHeaderOffset;
  u16						iscriptOffset;
  UNK						unknown2[2];
  u8						animation; //Use IscriptAnimation::Enum
  u8						wait;		// iscript sleep time
  u16						frameSet;
  u16						frameIndex;
  Point16					mapPosition;
  Point16					screenPosition;
  Box16						grpSize;	// Bounds for GRP frame, only different from normal when part of graphic is out of bounds.
  GrpHead					*grpOffset;
  void*						coloringData;        //?
  void*						renderFunction;		// renderFunction(this->screenPosition.x, this->screenPosition.y, this->getCurrentFrame(), &rctDraw, (int)this->coloringData)
  void*						updateFunction;
  CSprite					*parentSprite;
};

C_ASSERT(sizeof(CImage) == 64);
//static_assert(sizeof(CImage) == 64, "The size of the CImage structure is invalid");

#pragma pack()
