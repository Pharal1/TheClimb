// Map.cpp

#include "Map.h"

#include "../manager/UnitManager.h"
#include "../ent/Decor.h"

//Map::Map(TextureManager& textureManager) : textureManager_(textureManager) {}
Map::Map() {}



void Map::Load(std::string path, TextureManager& textureManager, UnitManager& unitManager) {
	std::ifstream file(path);
	json data;
	file >> data;

	x_ = data["width"];
	y_ = data["height"];

	textureManager.load(data["tileset_name"], data["tileset_path"]);
	tileSetName_ = data["tileset_name"];

	ground_ = data["ground"].get<std::vector<std::string>>();

	for (auto& [key, value] : data["tileset"].items()) {
		char id = key[0];

		TileType type;

		if (value["type"] == "Wall") {
			type = TileType::eWall;
		}
		else if (value["type"] == "Floor") {
			type = TileType::eFloor;
		}

		tileset_[id] = {
			type,
			value["index"]
		};
	}
	//auto& a = std::make_unique<Decor>(0, 0, 0, 0, nullptr, {"", "", 0})

	for (auto& [key, value] : data["objects"].items()) {
		std::cout << key << " " << value << std::endl;
		
		std::string type = value.at("type");

		if (type == "decor") {
			unitManager.addUnit<Decor>(
				value.at("x"),
				value.at("y"),
				0,
				TheClimb::kTileSize,
				textureManager,
				TextureData{ value.at("texture_name").get<std::string>(), value.at("texture_path").get<std::string>(),
				value.at("frames") }
			);
		}
	}


}

void Map::RenderGround(TextureManager& textureManager) const {
	int tileSize = TheClimb::kTileSize;
	Texture2D& tileTexture = textureManager.get(tileSetName_);

	for (int y = 0; y < y_; ++y) {
		for (int x = 0; x < x_; ++x) {
			Rectangle src{
				tileset_.at(ground_[y][x]).index * tileSize,
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
				tileTexture,
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
	if (isCellFree(tileset_.at(ground_[y][x]).type)) return true;
	return false;
}
