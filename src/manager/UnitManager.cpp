// UnitManager.cpp

#include "UnitManager.h"

void UnitManager::Render() {
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