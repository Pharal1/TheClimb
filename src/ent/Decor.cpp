// Decor.cpp

#include "Decor.h"

Decor::Decor(int posXTile,
	int posYTile,
	float velocity,
	TextureManager& manager,
	TextureData textureData
) : Unit(posXTile, posYTile, velocity, manager, textureData) {
}

void Decor::Render() {

	DrawTexturePro(
		texture_,
		{ (float)currentFrame_ * TheClimb::kTileSize, 0, TheClimb::kTileSize, TheClimb::kTileSize },
		{ posX_ - TheClimb::kTileSize / 2, posY_ - TheClimb::kTileSize / 2, TheClimb::kTileSize, TheClimb::kTileSize },
		{0, 0},
		0.f,
		WHITE
	);
	
}

void Decor::Update(float dt) {
	timer_ += dt;
	if (timer_ >= frameTime_) {
		timer_ = 0.f;
		currentFrame_++;
		if (currentFrame_ > textureData_.frames - 1) {
			currentFrame_ = 0;
		}
	}
}