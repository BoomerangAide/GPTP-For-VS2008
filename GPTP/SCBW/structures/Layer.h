#pragma once
#include "../../types.h"

//V241 for VS2008


namespace graphics { class Bitmap; }
struct bounds;

struct Layer {
  u8  buffers;
//u8  bits;
  u8  hasBeenRefreshed  : 1;
  u8  unk               : 7;
  u16 left;
  u16 top;
  u16 width;
  u16 height;
  u16 alignment;
  graphics::Bitmap  *pSurface;
  void (__stdcall *pUpdate)(graphics::Bitmap *pSurface, bounds *pBounds);
};

C_ASSERT(sizeof(Layer) == 20);
//static_assert(sizeof(Layer) == 20, "The size of the Layer structure is invalid");


struct Layers {
  Layer mouse;
  Layer context;
  Layer dialog;
  Layer placeBuildingA;
  Layer placeBuildingB;
  Layer game;
};
