//Unit.cpp

#include "Unit.h"

Unit::Unit
(
	int posXTile, 
	int posYTile,
	float velocity, 
	float size, 
	TextureManager& manager, 
	TextureData textureData) 
	: posXTile_(posXTile), 
	posYTile_(posYTile), 
	velocity_(velocity), 
	size_(size),
	targetTileX_(posXTile), 
	targetTileY_(posYTile), 
	textureData_(textureData
) {
	posX_ = posXTile_ * TheClimb::kTileSize + TheClimb::kTileSize / 2; //posX_ - size / 2 = posXTile_ * size
	posY_ = posYTile_ * TheClimb::kTileSize + TheClimb::kTileSize / 2;

	targetX_ = posX_;
	targetY_ = posY_;

	manager.load(textureData.textureID, textureData.texturePath);
	texture_ = manager.get(textureData.textureID);

	textureSource_ = { 0.0f, 0.0f, (float)texture_.width, (float)texture_.height };
	textureDest_ = { posX_, posY_, TheClimb::kTileSize, TheClimb::kTileSize };
	textureOrigin_ = { TheClimb::kTileSize / 2.0f, TheClimb::kTileSize };
}
void Unit::setPosTile(int x, int y) {
	if (map_ == nullptr) return;
	if (!map_->isFree(x, y)) {
		return;
	}

	posXTile_ = x;
	posYTile_ = y;

	posX_ = posXTile_ * TheClimb::kTileSize + TheClimb::kTileSize / 2;
	posY_ = posYTile_ * TheClimb::kTileSize + TheClimb::kTileSize / 2;
}

void Unit::setPosTileX(int x) {
	if (getMap() == nullptr) return;
	posXTile_ = x;

	posX_ = posXTile_ * TheClimb::kTileSize + TheClimb::kTileSize / 2;
}
void Unit::setPosTileY(int y) {
	if (getMap() == nullptr) return;
	posYTile_ = y;

	posY_ = posYTile_ * TheClimb::kTileSize + TheClimb::kTileSize / 2;
}

void Unit::interract() {

}