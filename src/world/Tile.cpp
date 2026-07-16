//Tile.cpp

#include "Tile.h"

Tile tileSet[256];

void initTileSet() {
	tileSet['0'] = { TileType::eFloor, GREEN, 1}; //C:\dev\cpp\raylib\TheClimb\src\resources\grass.png
	tileSet['1'] = { TileType::eWall, BROWN, 0}; //C:\dev\cpp\raylib\TheClimb\src\resources\wall(stone).png
	tileSet['2'] = { TileType::eWall, SKYBLUE, 2};
}