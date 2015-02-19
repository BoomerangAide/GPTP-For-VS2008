#ifdef MOD_IN_PROGRESS

#pragma once
#include "common.h"

struct PLAYER {

  u32   id;
  u32   actions;    //Unused; FF FF FF FF if not a human player
  u8    type;
  u8    race;       //Use with scbw::RaceId
  u8    force;
  char  name[25];

  u8 getColor();

};
#endif