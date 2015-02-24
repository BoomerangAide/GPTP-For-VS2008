#pragma once
#include "common.h"

//Not like the advanced BWAPI class
struct PLAYER {

  u32   id;
  u32   actions;    //Unused; FF FF FF FF if not a human player
  u8    type;
  u8    race;       //Use with scbw::RaceId
  u8    force;
  char  name[25];

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
