// UnitManager.cpp

#include "UnitManager.h"

#include "../ent/Player.h"
#include "../ent/Npc.h"
#include "CameraManager.h"

Player& UnitManager::CreatePlayer(int posXTile, int posYTile, float velocity, TextureManager& manager, TextureData textureData) {
	auto player = std::make_unique<Player>(posXTile, posYTile, velocity, manager, textureData);
	player_ = player.get();
	player->setUnitManager(this);

	units_.push_back(std::move(player));

	return *player_;
}

void UnitManager::Render(Player& player, const CameraManager& cameraManager) {
	Color color = { 0, 0, 0, 128 };
	int renderUnits = 0;
	std::sort(
		units_.begin(),
		units_.end(),
		[](const auto& a, const auto& b) {
			return a->getPosY() < b->getPosY();
		}
	);

		Vector2 topLeft = GetScreenToWorld2D({ -static_cast<float>(TheClimb::kTileSize * 2), -static_cast<float>(TheClimb::kTileSize * 2) }, cameraManager.GetCamera());
		Vector2 botRight = GetScreenToWorld2D(
			{
				static_cast<float>(GetScreenWidth()) + static_cast<float>(TheClimb::kTileSize * 2),
				static_cast<float>(GetScreenHeight()) + static_cast<float>(TheClimb::kTileSize * 2)
			},
			cameraManager.GetCamera()
		);
	for (auto& unit : units_) {
		if (
			(unit->getPosX() < topLeft.x || unit->getPosX() > botRight.x)
			||  (unit->getPosY() < topLeft.y || unit->getPosY() > botRight.y)
			) {
			continue;
		}

		DrawEllipse(unit->getPosX(), unit->getPosY() + TheClimb::kTileSize / 4, TheClimb::kTileSize / 3, TheClimb::kTileSize / 4, color);
		unit->Render();
		renderUnits++;
	}
}

bool UnitManager::collision(int posTileX, int posTileY, Unit* ignore) const {
	for (const auto& unit : units_) {
		if (unit.get() == ignore) continue;
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

void UnitManager::Update(float dt) {
	for (const auto& unit : units_) {
		unit->Update(dt);
	}
}