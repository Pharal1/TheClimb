// UnitManager.cpp

#include "UnitManager.h"

#include "../ent/Player.h"
#include "../ent/Npc.h"

Player& UnitManager::CreatePlayer(int posXTile, int posYTile, float velocity, float size, TextureManager& manager, const char* textureID, const char* texturePath) {
	auto player = std::make_unique<Player>(posXTile, posYTile, velocity, size, manager, textureID, texturePath);
	player_ = player.get();
	player->setUnitManager(this);

	units_.push_back(std::move(player));

	return *player_;
}

void UnitManager::Render(Player& player) {
	std::sort(
		units_.begin(),
		units_.end(),
		[](const auto& a, const auto& b) {
			return a->getPosY() < b->getPosY();
		}
	);

	for (auto& unit : units_) {
		unit->Render();
	}
}

bool UnitManager::collision(int posTileX, int posTileY) const {
	for (const auto& unit : units_) {
		std::cout << "UnitManager: " << (unit->getPosYTile() == posTileY) << (unit->getPosXTile() == posTileX) << std::endl;
		if (unit->getPosXTile() == posTileX && unit->getPosYTile() == posTileY) return true;
		
	}
	return false;
}

Interactable* UnitManager::getInteractableAt(int x, int y) {
	
	for (const auto& unit : units_) {
		if (unit->getPosXTile() != x || unit->getPosYTile() != y) {
			continue;
		}
		return dynamic_cast<Interactable*>(unit.get());
	}
	return nullptr;
}