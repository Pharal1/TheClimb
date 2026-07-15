//Tile.cpp

#include "Tile.h"

Tile tileSet[256];

void initTileSet() {
	tileSet['0'] = { TileType::eFloor, GREEN };
	tileSet['1'] = { TileType::eWall, BROWN };
	tileSet['2'] = { TileType::eWall, SKYBLUE };
}