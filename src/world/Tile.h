//Tile.h

#ifndef TILE_H_
#define TILE_H_

#include "raylib.h"
#include <string>


enum class TileType {
	eWall,
	eFloor
};

struct Tile {
	TileType type;
	int index;
};

//extern Tile tileSet[256];
//void initTileSet();

#endif