// Map.h

#ifndef MAP_H_
#define MAP_H_

#include <iostream>
#include <vector>
#include <string>
#include "raylib.h"
#include <nlohmann/json.hpp>
#include <fstream>

#include "Tile.h"
#include "../manager/TextureManager.h"
#include "../consts.h"

using json = nlohmann::json;

bool isCellFree(TileType tileType);

class Map {
public:
	//Map(TextureManager& textureManager);
	Map();
	void Load(std::string path, TextureManager& textureManager);
	void RenderGround(TextureManager& textureManager) const;
	bool isFree(int x, int y) const;
	//void const setTextureManager(TextureManager* textureManager) { textureManager_ = textureManager; }
private:
	std::vector<std::string> ground_;
	
	std::string tileSet_ = "";
	int x_{};
	int y_{};

	//TextureManager* textureManager_ = nullptr;
};

#endif // !MAP_H_
