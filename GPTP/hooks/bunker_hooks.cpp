#include "bunker_hooks.h"
#include <SCBW/scbwdata.h>
#include "../SCBW/enumerations.h"

//V241 for VS2008

//Helper function declarations. Do NOT modify!
namespace {

CThingy* createThingy(u16 spriteId, s16 x, s16 y, u8 playerId = 0);
void setImageDirection(CImage *image, s8 direction);
void setThingyVisibilityFlags(CThingy *thingy);

} //unnamed namespace

namespace hooks {

/// Checks whether the unit can attack from inside a bunker.
bool unitCanAttackInsideBunkerHook(const CUnit *unit) {
  //Default StarCraft behavior
  const u16 unitId = unit->id;
  if (unitId == UnitId::TerranMarine
      || unitId == UnitId::Hero_JimRaynorMarine
      || unitId == UnitId::TerranGhost
      || unitId == UnitId::Hero_SarahKerrigan
      || unitId == UnitId::Hero_AlexeiStukov
      || unitId == UnitId::Hero_SamirDuran
      || unitId == UnitId::Hero_InfestedDuran
      || unitId == UnitId::TerranFirebat
      || unitId == UnitId::Hero_GuiMontag)
    return true;
  else
    return false;
}

void createBunkerAttackThingyHook(const CUnit *unit) {
  //Default StarCraft behavior
  CImage *bunkerImage = unit->connectedUnit->sprite->mainGraphic;

  u8 frameDirection = (unit->currentDirection1 + 16) / 32 % 8;
  const LO_Header *loFile = lo_files->attackOverlays[bunkerImage->id];
  Point8 offset = loFile->getOffset(bunkerImage->frameIndex, frameDirection);
  
  if (bunkerImage->flags & 0x2) //Is inverted
    offset.x = -offset.x;

  u8 frameAngle;
  u16 spriteId;

  if (unit->id == UnitId::firebat || unit->id == UnitId::gui_montag) {
    frameAngle = ((unit->currentDirection1 + 8) / 16 % 16) * 16;
    spriteId = 378; //Firebat flamethrower graphics
  }
  else {
    frameAngle = frameDirection * 32;
    spriteId = 377; //Bunker attack overlay
  }

  CThingy *bunkerAttackEffect = createThingy(spriteId,
                                             offset.x + unit->getX(),
                                             offset.y + unit->getY());
  if (!bunkerAttackEffect) return;

  bunkerAttackEffect->sprite->elevationLevel = unit->sprite->elevationLevel + 1;
  for (CImage *image = bunkerAttackEffect->sprite->images.head;
       image; image = image->link.next) {
    setImageDirection(image, frameAngle);
  }
  setThingyVisibilityFlags(bunkerAttackEffect);
}

} //hooks


//-------- Helper function definitions. Do NOT modify! --------//

namespace {

const u32 Func_CreateThingy = 0x00488210;
CThingy* createThingy(u16 spriteId, s16 x, s16 y, u8 playerId) {
  static CThingy *thingy;
  s32 x_ = x, playerId_ = playerId;
  u32 spriteId_ = spriteId;

  __asm {
    PUSHAD
    PUSH playerId_
    MOV DI, y
    PUSH x_
    PUSH spriteId_
    CALL Func_CreateThingy
    MOV thingy, EAX
    POPAD
  }

  return thingy;
}

const u32 Func_SetImageDirection = 0x004D5F80;
void setImageDirection(CImage *image, s8 direction) {
  u32 direction_ = direction;

  __asm {
    PUSHAD
    PUSH direction_
    MOV ESI, image
    CALL Func_SetImageDirection
    POPAD
  }
}

const u32 Func_SetThingyVisibilityFlags = 0x004878F0;
void setThingyVisibilityFlags(CThingy *thingy) {
  __asm {
    PUSHAD
    MOV ESI, thingy
    CALL Func_SetThingyVisibilityFlags
    POPAD
  }
}

};