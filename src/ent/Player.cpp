// Player.cpp
#include "Player.h"


Player::Player(int posXTile, int posYTile, float velocity, float size, TextureManager& manager, const char* textureID, const char* texturePath) 
	: Unit(posXTile, posYTile, velocity, size, manager, textureID, texturePath) {
}

void Player::Input(Vector2 dm, bool isRunning, bool isEPressed) {
	dm_ = dm;
	isRunning_ = isRunning;
	isEPressed_ = isEPressed;

	//std::cout << npc_ << std::endl;
}

void Player::Update(float dt) {
	const float tileSize = getMap()->getTileSize();

	float multiplier = 1.0f;
	if (isRunning_) multiplier *= velocityRunningMultiplier_;

	

	if (!isMoving_)
	{



		int nextX = posXTile_;
		int nextY = posYTile_;
		//std::cout << "1" << std::endl;
		if (dm_.x != 0)
			nextX += (int)dm_.x;
		else if (dm_.y != 0)
			nextY += (int)dm_.y;
		else {

			if (isEPressed_) std::cout << "E PRESSED!" << std::endl;

			return;
		}

		dirX_ = (float)(nextX - posXTile_);
		dirY_ = (float)(nextY - posYTile_);

		if (!getMap()->isFree(nextX, nextY)) return;
		for (Npc* npc : npc_) {
			if (npc->getPosXTile() == nextX && npc->getPosYTile() == nextY) return;
		}
		targetTileX_ = nextX;
		targetTileY_ = nextY;

		

		isMoving_ = true;
	}
	else {
		//std::cout << "exp: " << (fabs(targetTileX_ * size_ - posX_) <= velocity_ * dt) << std::endl;
		//std::cout << "exp: " << (fabs(targetTileY_ * size_ + size_/2 - posY_) <= velocity_ * dt) << std::endl;
		if (fabs(targetTileX_ * size_ + size_/2 - posX_) <= velocity_ * dt && fabs(targetTileY_ * size_ + size_ / 2 - posY_) <= velocity_ * dt ){
			setPosTileX(targetTileX_);
			setPosTileY(targetTileY_);
			isMoving_ = false;
			//std::cout << "IsMoving_: " << isMoving_ << std::endl;
			return;
		}
		else {
			posX_ += dirX_ * dt * velocity_;
			posY_ += dirY_ * dt * velocity_;
		}
	}
}

void Player::Render() {
	float posX = posX_;
	float posY = posY_;
	float size = size_;

	textureDest_ = { posX, posY - (float)texture_.width / 2, (float)texture_.width, (float)texture_.height };
	DrawTexturePro(texture_, textureSource_, textureDest_, textureOrigin_, 0.0f, WHITE);
	//DrawTexture(texture_, 0, 0, WHITE);
	//std::cout << "Player::Render() called" << std::endl;
}


