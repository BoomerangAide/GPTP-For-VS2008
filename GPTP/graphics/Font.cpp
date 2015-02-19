//Based on BWAPI's BW/Font.cpp
#include "Font.h"
#include "../SCBW/scbwdata.h"
#include <cassert>

namespace graphics {

FontChar* Font::getChar(char c) const {
  u8 ch = (u8)c;
  if (this != NULL
      && this->low <= ch && ch <= this->high
      && this->chrs[ch - this->low] != (FontChar*)this)
    return this->chrs[ch - this->low];
  return NULL;
}

int Font::getCharWidth(char c) const {
  switch (c) {
    case '\t':
      return this->maxWidth() * 2;
    case ' ':
      return this->maxWidth() / 2;
    default:
      return this->getChar(c)->getWidth();
  }
}

// ----------------- GET WIDTH ---------------------
int Font::getTextWidth(const char *pszStr) const {
  // verify valid size index
  assert(this);
  if (!pszStr) return 0;

  // Retrieve size
  int size = 0;
  for (; *pszStr; ++pszStr)
    size += this->getCharWidth(*pszStr);
  return size;
}

// ----------------- GET WIDTH ---------------------
int Font::getTextHeight(const char *pszStr) const {
  // verify valid size index
  if (!pszStr || this == NULL) return 0;

  int size = this->yMax;
  for (; *pszStr; ++pszStr) {
    if (*pszStr == '\n')
      size += this->yMax;
  }
  return size;
}

int Font::maxWidth() const {
  if (this != NULL)
    return this->xMax;
  return 0;
}

int Font::maxHeight() const {
  if (this != NULL)
    return this->yMax;
  return 0;
}

int Font::getTextWidth(const char *pszStr, int size) {
  if (0 <= size && size <= 3)
    return fontBase[size]->getTextWidth(pszStr);
  return 0;
}

int Font::getTextHeight(const char *pszStr, int size) {
  if (0 <= size && size <= 3)
    return fontBase[size]->getTextHeight(pszStr);
  return 0;
}

// ---------------- FontChar ----------------

int FontChar::getWidth() const {
  if (this != NULL)
    return this->width;
  return 0;
}

int FontChar::getHeight() const {
  if (this != NULL)
    return this->height;
  return 0;
}

int FontChar::getX() const {
  if (this != NULL)
    return this->x;
  return 0;
}

int FontChar::getY() const {
  if (this != NULL)
    return this->y;
  return 0;
}

int FontChar::colorMask(int index) const {
  assert(this != NULL);
  return this->data[index] & 7;
}

int FontChar::pixelOffset(int index) const {
  assert(this != NULL);
  return this->data[index] >> 3;
}

} //graphics
