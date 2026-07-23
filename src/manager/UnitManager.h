// UnitManager.h

#pragma once

#include <vector>
#include <memory>
#include <algorithm>

#include "../ent/Unit.h"
#include "../ent/Npc.h"

class UnitManager {
public:
	void Render();

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

private:
	std::vector<std::unique_ptr<Unit>> units_;
};