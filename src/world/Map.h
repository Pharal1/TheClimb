// Map.h
/*
'0' = floor
'1' = wall
'2' = water





*/
#ifndef MAP_H_
#define MAP_H_

#include <iostream>
#include <vector>
#include <string>
#include "raylib.h"
#include "Tile.h"
#include "../manager/TextureManager.h"

bool isCellFree(TileType tileType);

struct MapData {
	std::vector<std::string> map_;
	int cellSize_;

	MapData(std::vector<std::string> map, int cellSize);
};

class Map {
public:
	Map(MapData mapData);
	void Render();
	void Load(TextureManager* textureManager);
	bool isFree(int x, int y);
	int getTileSize() const { return mapData_.cellSize_; }
private:
	std::vector<std::vector<TileType>> map_;
	MapData mapData_;
	Texture2D tileset_{};

	int maxY_ = 0;
	int maxX_ = 0;
};

#endif // !MAP_H_
