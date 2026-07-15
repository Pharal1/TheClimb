// Player.cpp
#include "Player.h"

Player::Player(int posXTile, int posYTile, const char* texturePath, float velocity, float size) : posXTile_(posXTile), posYTile_(posYTile), velocity_(velocity), size_(size), targetTileX_(posXTile), targetTileY_(posYTile) {
	posX_ = posXTile_ * size + size / 2; //posX_ - size / 2 = posXTile_ * size
	posY_ = posYTile_ * size + size / 2;
	
	texture_ = LoadTexture(texturePath);
	textureSource = { 0.0f, 0.0f, (float)texture_.width, (float)texture_.height };
	textureDest = { posX_, posY_, size, size };
	textureOrigin = { size / 2.0f, size / 2.0f };
	
}

Player::~Player() {
	UnloadTexture(texture_);
}

void Player::Update(float dt, Vector2 dm, bool isRunning) {
	//std::cout << "Player::Update() is called\n";
	/*
	Player::Update(float dt, Vector2 dm, bool isRunning)

	float mlpr = 1.0f;
	float vel_diag_m = 0.7f;
	if (isRunning) mlpr = velocityRunningMultiplier;

	if (!isMovingX_ && dm.x != 0) {
		if (map_->isFree(targetTileX_ + dm.x, posYTile_))
		{
			targetTileX_ += dm.x;

			dirX_ = dm.x;
			isMovingX_ = true;

			//std::cout << targetTileX_ << dm.x << map_->isFree(targetTileX_ + dm.x, posYTile_) << std::endl;
		}
		else {
			targetTileX_ = posXTile_;
			//std::cout << targetTileX_ << std::endl;
		}
	}
	if (!isMovingY_ && dm.y != 0) {
		if (map_->isFree(posXTile_, targetTileY_ + dm.y)) {
			targetTileY_ += dm.y;

			dirY_ = dm.y;
			isMovingY_ = true;
		}
		else {
			targetTileY_ = posYTile_;
		}
	}
	if (isMovingX_) {
		if ((targetTileX_ * size_ + size_ / 2) - posX_ < 0.5f && (targetTileX_ * size_ + size_ / 2) - posX_ > -0.5f) {
			setPosTileX(targetTileX_);
			isMovingX_ = false;
			dirX_ = 0;
		}
		else {
			if (!isMovingY_) {
				posX_ += dirX_ * dt * velocity_ * mlpr;
			}
			else {
				posX_ += dirX_ * dt * velocity_ * vel_diag_m * mlpr;
			}
		}
	}
	if (isMovingY_) {
		if ((targetTileY_ * size_ + size_ / 2) - posY_ < 0.5f && (targetTileY_ * size_ + size_ / 2) - posY_ > -0.5f) {
			setPosTileY(targetTileY_);
			isMovingY_ = false;
			dirY_ = 0;
		}
		else {
			if (!isMovingX_) {
				posY_ += dirY_ * dt * velocity_ * mlpr;
			}
			else {
				posY_ += dirY_ * dt * velocity_ * vel_diag_m * mlpr;
			}
		}
	}
	*/
	const float tileSize = map_->getTileSize();
	if (!isMoving_)
	{
		int nextX = posXTile_;
		int nextY = posYTile_;
		//std::cout << "1" << std::endl;
		if (dm.x != 0)
			nextX += (int)dm.x;
		else if (dm.y != 0)
			nextY += (int)dm.y;
		else return;
		if (map_->isFree(nextX, nextY))
		{
			targetTileX_ = nextX;
			targetTileY_ = nextY;

			dirX_ = (float)(nextX - posXTile_);
			dirY_ = (float)(nextY - posYTile_);

			isMoving_ = true;
		}
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

	textureDest = { posX, posY, size, size };
	DrawTexturePro(texture_, textureSource, textureDest, textureOrigin, 0.0f, WHITE);
}

void Player::setPosTile(int x, int y) {
	if (map_ == nullptr) return;
	if (!map_->isFree(x, y)) {
		return;
	}
	
	posXTile_ = x;
	posYTile_ = y;

	posX_ = posXTile_ * size_ + size_ / 2;
	posY_ = posYTile_ * size_ + size_ / 2;
}

void Player::setPosTileX(int x) {
	if (map_ == nullptr) return;
	/*if (x > map_->getSizeX()) {
		std::cout << "setPosTileX() out of array range" << std::endl;
		return;
	}
	*/
	posXTile_ = x;

	posX_ = posXTile_ * size_ + size_ / 2;
}
void Player::setPosTileY(int y) {
	if (map_ == nullptr) return;
	/*if (y > map_->getSizeY()) {
		std::cout << "setPosTileY() out of array range" << std::endl;
		return;
	}
	*/
	posYTile_ = y;

	posY_ = posYTile_ * size_ + size_ / 2;
}
