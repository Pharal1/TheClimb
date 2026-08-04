// Map.h

#ifndef MAP_H_
#define MAP_H_

#include <iostream>
#include <vector>
#include <string>
#include "raylib.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <unordered_map>

#include "Tile.h"
#include "../manager/TextureManager.h"
#include "../consts.h"

class UnitManager;
class DialogueManager;



bool isCellFree(TileType tileType);

class Map {
public:
	//Map(TextureManager& textureManager);
	Map();
	void Load(std::string path, TextureManager& textureManager, UnitManager& unitManager, DialogueManager& dialogueManager);
	void RenderGround(TextureManager& textureManager) const;
	bool isFree(int x, int y) const;

	int GetSizeX() const { return x_; }
	int GetSizeY() const { return y_; }
	//void const setTextureManager(TextureManager* textureManager) { textureManager_ = textureManager; }
private:
	std::vector<std::string> ground_;
	
	std::string tileSetName_ = "";
	std::unordered_map<char, Tile> tileset_;

	int x_{};
	int y_{};

	//TextureManager* textureManager_ = nullptr;
};

#endif // !MAP_H_
