// Map.cpp

#include "Map.h"

//Map::Map(TextureManager& textureManager) : textureManager_(textureManager) {}
Map::Map() {}


void Map::Load(std::string path, TextureManager& textureManager) {
	std::ifstream file(path);
	json data;
	file >> data;

	x_ = data["width"];
	y_ = data["height"];

	textureManager.load(data["tileset"], data["tileset_path"]);
	tileSet_ = data["tileset"];

	ground_ = data["ground"].get<std::vector<std::string>>();

}

void Map::RenderGround(TextureManager& textureManager) const {
	int tileSize = TheClimb::kTileSize;
	for (int y = 0; y < y_; ++y) {
		for (int x = 0; x < x_; ++x) {
			Rectangle src{
				tileSet[ground_[y][x]].index * tileSize,
				0.0f,
				tileSize,
				tileSize
			};
			Rectangle dst{
				x * tileSize,
				y * tileSize,
				tileSize,
				tileSize
			};
			DrawTexturePro(
				textureManager.get(tileSet_),
				src,
				dst,
				{ 0, 0 },
				0.0f,
				WHITE
			);
		}
	}
}

bool isCellFree(TileType tileType) {
	if (tileType == TileType::eFloor) return true;
	return false;
}
bool Map::isFree(int x, int y) const {
	if (x >= x_ || x < 0 || y >= y_ || y < 0) {
		std::cout << "Map::isFree() out of range" << std::endl;
		return false;
	}
	if (isCellFree(tileSet[ground_[y][x]].type)) return true;
	return false;
}
