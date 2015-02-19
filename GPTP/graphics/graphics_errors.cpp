#include "graphics_errors.h"
#include "Bitmap.h"
#include "../SCBW/scbwdata.h"

namespace graphics {

int errorFlags;

void setError(GraphicsErrorId error) {
  errorFlags |= error;
}

void clearErrors() {
  errorFlags = 0;
}

void drawErrorMessages() {

#ifndef NDEBUG

  if (errorFlags & ERR_TOO_MANY_SHAPES) {
    gameScreenBuffer->blitString("Error: Too many shapes!", 10, 10, 2);
  }

  if (errorFlags & ERR_TOO_MANY_STRINGS) {
    gameScreenBuffer->blitString("Error: Too many strings!", 10, 40, 2);
  }

  if (errorFlags & ERR_UNKNOWN_SHAPE) {
    gameScreenBuffer->blitString("Error: Unknown shape found.", 10, 70, 2);
  }

  if (errorFlags & ERR_UNKNOWN_COORD_TYPE) {
    gameScreenBuffer->blitString("Error: Unknown coordinate type found.", 10, 100, 2);
  }

#endif

};

} //graphics
