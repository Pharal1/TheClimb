//Unit.cpp

#include "Unit.h"

Unit::Unit(int posXTile, int posYTile, float velocity, float size, TextureManager& manager, const char* textureID, const char* texturePath) : posXTile_(posXTile), posYTile_(posYTile), velocity_(velocity), size_(size), targetTileX_(posXTile), targetTileY_(posYTile) {
	posX_ = posXTile_ * size + size / 2; //posX_ - size / 2 = posXTile_ * size
	posY_ = posYTile_ * size + size / 2;

	manager.load(textureID, texturePath);
	texture_ = manager.get(textureID);

	textureSource_ = { 0.0f, 0.0f, (float)texture_.width, (float)texture_.height };
	textureDest_ = { posX_, posY_, size_, size_ };
	textureOrigin_ = { size_ / 2.0f, size_ };
}
void Unit::setPosTile(int x, int y) {
	if (map_ == nullptr) return;
	if (!map_->isFree(x, y)) {
		return;
	}

	posXTile_ = x;
	posYTile_ = y;

	posX_ = posXTile_ * size_ + size_ / 2;
	posY_ = posYTile_ * size_ + size_ / 2;
}