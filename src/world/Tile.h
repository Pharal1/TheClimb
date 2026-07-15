//Tile.h

#ifndef TILE_H_
#define TILE_H_

#include "raylib.h"

enum class TileType {
	eWall,
	eFloor
};

struct Tile {
	TileType type;
	Color color;
};

extern Tile tileSet[256];
void initTileSet();

#endif