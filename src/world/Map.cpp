// Map.cpp

#include "Map.h"

#include "../manager/UnitManager.h"
#include "../ent/Decor.h"
#include "../ent/Npc.h"
#include "../util.h"
#include "../manager/dialogue/DialogueManager.h"

using json = nlohmann::json;

//Map::Map(TextureManager& textureManager) : textureManager_(textureManager) {}
Map::Map() {}



void Map::Load(std::string path, TextureManager& textureManager, UnitManager& unitManager, DialogueManager& dialogueManager) {

	json data;

	if (!Util::LoadJson(path, data)) {
		return;
	}

	if (!Util::Contains(data, "MAP", "width")) {
		return;
	}
	if (!Util::Contains(data, "MAP", "height")) {
		return;
	}
	if (!Util::Contains(data, "MAP", "tileset_name")) {
		return;
	}
	if (!Util::Contains(data, "MAP", "tileset_path")) {
		return;
	}
	if (!Util::Contains(data, "MAP", "ground")) {
		return;
	}
	if (!Util::Contains(data, "MAP", "tileset")) {
		return;
	}

	x_ = data["width"];
	y_ = data["height"];

	textureManager.load(data["tileset_name"], data["tileset_path"]);
	tileSetName_ = data["tileset_name"];

	ground_ = data["ground"].get<std::vector<std::string>>();

	for (auto& value : data["tileset"]) {
		char id = value.value("char", (std::string)"0")[0];

		TileType type = TileType::eWall;

		std::string typeName = value.value("type", "Wall");

		if (typeName == "Wall") {
			type = TileType::eWall;
		}
		else if (typeName == "Floor") {
			type = TileType::eFloor;
		}

		tileset_[id] = {
			type,
			value.value("index", 0)
		};
	}

	if (!Util::Contains(data, "MAP", "objects")) {
		return;
	}

	for (auto& value : data["objects"]) {
		if (!Util::Contains(value, "MAP", "type", "objects")) {
			continue;
		}
		if (!Util::Contains(value, "MAP", "texture_path", "objects")) {
			continue;
		}
		if (!Util::Contains(value, "MAP", "texture_name", "objects")) {
			continue;
		}

		std::string type = value["type"];

		if (type == "decor") {
			unitManager.addUnit<Decor>(
				value.value("x", 0),
				value.value("y", 0),
				0,
				TheClimb::kTileSize,
				textureManager,
				TextureData{ value.at("texture_name").get<std::string>(), value.at("texture_path").get<std::string>(), value.value("frames", 1) }
			);
		}
		else if (type == "npc") {
			auto& npc = unitManager.addUnit<Npc>(
				value.value("x", 0),
				value.value("y", 0),
				value.value("velocity", TheClimb::kNpcVelocity),
				TheClimb::kTileSize,
				textureManager,
				dialogueManager,
				TextureData{ value.at("texture_name").get<std::string>(), value.at("texture_path").get<std::string>(), value.value("frames", 1) }
			);
			std::string dialogue;
			//if (Util::Contains(value, "MAP", "dialogue_path", false)) {
			dialogue = value.value<std::string>("dialogue_path", "");
			
			if (dialogue != "") {
				dialogueManager.LoadDialogue(dialogue);
				npc.SetDialogue(dialogueManager.LoadDialogue(dialogue));
			}
			

			
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
