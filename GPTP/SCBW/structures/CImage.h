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


////////////////////////////////////////////////////////////////
//Actual data structure
  CLink<CImage> link;
  u16         id;


/// ++Drawing function (values are the same as DataEdit)
/// officially "ubRLE"\
/// 00 = RLE_NORMAL, 01 = RLE_1,
/// 02 = RLE_2, 03 = RLE_3,
/// 04 = RLE_4, 05 = RLE_CLOAK,
/// 06 = RLE_CLOAKED, 07 = RLE_DECLOAK,
/// 08 = RLE_8, 09 = RLE_EFFECT,
/// 10 = RLE_SHADOW, 11 = RLE_HPFLOATDRAW,
/// 12 = RLE_WARP, 13 = RLE_OUTLINE,
/// 14 = RLE_PLAYER_SIDE, 15 = RLE_15,
/// 16 = RLE_SHIFT, 17 = RLE_FIRE

  u8          paletteType;   			
  u8          direction;

			/// 0x0001  - redraw
			/// 0x0002  - flipped/mirrored
			/// 0x0004  - don't update ?
			/// 0x0008  - has rotation frames
			/// 0x0010  -
			/// 0x0020  - clickable
			/// 0x0040  - hidden/invisible (don't draw)
			/// 0x0080  -
			/// 0x0100  -
			/// 0x0200  -
			/// 0x0400  -
			/// 0x0800  -
			/// 0x1000  -
			/// 0x2000  -
			/// 0x4000  -
			/// 0x8000  -			  
  u16         flags;
  u8          horizontalOffset;
  u8          verticalOffset;
  u16         iscriptHeaderOffset;
  u16         iscriptOffset;
  UNK         unknown2[2];
  u8          animation;
  u8          wait;		// iscript sleep time
  u16         frameSet;
  u16         frameIndex;
  Point16     mapPosition;
  Point16     screenPosition;
  Box16       grpSize;	// Bounds for GRP frame, only different from normal when part of graphic is out of bounds.
  GrpHead     *grpOffset;
  void*       coloringData;        //?
  void*       renderFunction;		// renderFunction(this->screenPosition.x, this->screenPosition.y, this->getCurrentFrame(), &rctDraw, (int)this->coloringData)
  void*       updateFunction;
  CSprite     *parentSprite;
};

C_ASSERT(sizeof(CImage) == 64);
//static_assert(sizeof(CImage) == 64, "The size of the CImage structure is invalid");

#pragma pack()
