#pragma once
#include "common.h"

//Not like the advanced BWAPI class
struct PLAYER {

/*00*/  u32   id;
/*04*/  u32   actions;    //Unused; FF FF FF FF if not a human player
/*08*/	u8    type;
/*09*/  u8    race;       //Use with scbw::RaceId
/*0A*/  u8    force;
/*0B*/  char  name[25];

/*struct size = 36 (0x24)*/

  /// return the possibly non-standard color of the 
  /// current player
  u8 getColor();
  
  /// return the possibly non-standard color of the 
  /// player identified by PlayerId
  static u8 getColor(u8 playerId);

  /// return the faction (tribe, brood or other) color 
  ///of current player
  u8 getFactionColor();

  /// return the faction (tribe, brood or other) color 
  /// of the player identified by PlayerId
  static u8 getFactionColor(u8 playerId);

};
