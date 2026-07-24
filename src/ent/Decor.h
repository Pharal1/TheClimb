// Decore.h

#pragma once

#include "Unit.h"
#include "../consts.h"

class Decor : public Unit {
public:
	Decor(int posXTile,
		int posYTile,
		float velocity,
		float size,
		TextureManager& manager,
		TextureData textureData
	);
	void Render() override;
	void Update(float dt) override;

	~Decor() { std::cout << "Decor destroyer\n"; }
private:
	float timer_ = 0.f;
	float frameTime_ = 1.f;
};