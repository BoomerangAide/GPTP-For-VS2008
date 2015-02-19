#ifdef MOD_IN_PROGRESS

#include <cassert>
#include "Player.h"
#include "../api.h"
#include "../enumerations.h"
#include "../../graphics/graphics.h"

// Return the proper ColorId to use an unit current color with graphics function
graphics::ColorId PLAYER::getColor() {
	assert(this);

	//store a playerId until the end where it will properly store a ColorId
	graphics::ColorId return_value;

	//for normal players, apply colors switching
	if(this->id >= 0 && this->id <= 7) {

		// get the proper playerId in multiplayer game (don't break campaigns/UMS)
		return_value = colorReordering[this->id];

		//fix BROWN to GREEN color swap in Desert map
		if(*CURRENT_TILESET == TilesetType::Desert && return_value == 5)
			return_value = 8;
		
		//fix WHITE to GREEN color swap in Ice map
		if(*CURRENT_TILESET == TilesetType::Ice && return_value == 6)
			return_value = 8;

	}
	else
		return_value = this->id;

	return_value = graphics::playersColors[return_value];

	return return_value;

}

#endif