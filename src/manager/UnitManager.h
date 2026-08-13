// UnitManager.h

#pragma once

#include <vector>
#include <memory>
#include <algorithm>

#include "../ent/Unit.h"
#include "CameraManager.h"

class Player;

class UnitManager {
public:
    Player& CreatePlayer(int posXTile, int posYTile, float velocity, TextureManager& manager, TextureData textureData);

	void Render(Player& player, const CameraManager& cameraManager);
    void Update(float dt);

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
    bool collision(int posTileX, int posTileY, Unit* ignore) const;

    Interactable* getInteractableAt(int x, int y);
    Player& getPlayer() { return *player_; }

private:
    Player* player_ = nullptr;
    std::vector<std::unique_ptr<Unit>> units_;

};