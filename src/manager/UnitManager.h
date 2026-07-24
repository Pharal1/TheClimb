// UnitManager.h

#pragma once

#include <vector>
#include <memory>
#include <algorithm>

#include "../ent/Unit.h"

class Player;

class UnitManager {
public:
    Player& CreatePlayer(int posXTile, int posYTile, float velocity, float size, TextureManager& manager, const char* textureID, const char* texturePath);

	void Render(Player& player);

    template<typename T, typename... Args>
    T& addUnit(Args&&... args)
    {
        auto unit = std::make_unique<T>(
            std::forward<Args>(args)...
        );

        T& ref = *unit;

        units_.push_back(std::move(unit));

        return ref;
    }
    bool collision(int posTileX, int posTileY) const;

    Interactable* getInteractableAt(int x, int y);
    Player& getPlayer() { return *player_; }

private:
    Player* player_ = nullptr;
    std::vector<std::unique_ptr<Unit>> units_;

};