// Player.cpp
#include "Player.h"
#include "../manager/UnitManager.h"


Player::Player(int posXTile, int posYTile, float velocity, float size, TextureManager& manager, TextureData textureData)
	: Unit(posXTile, posYTile, velocity, size, manager, textureData) {
}

void Player::Input(Util::HandleInput handleInputData) {
	dm_ = handleInputData.deltaPlayer;
	isRunning_ = handleInputData.isRunning;
	isEPressed_ = handleInputData.isEPressed;
}

void Player::Update(float dt) {
	const float tileSize = (float)TheClimb::kTileSize;

	float totalVelocity = velocity_;

	if (isRunning_) totalVelocity *= velocityRunningMultiplier_;

	if (!isMoving_)
	{

		if (dm_.x == 0 && dm_.y == 0) return;

		dirX_ = dm_.x;
		dirY_ = dm_.y;
		
		float nextTargetX = posX_ + static_cast<float>((dm_.x * TheClimb::kTileSize));
		float nextTargetY = posY_ + static_cast<float>((dm_.y * TheClimb::kTileSize));

		int nextX = static_cast<int>(nextTargetX / TheClimb::kTileSize);
		int nextY = static_cast<int>(nextTargetY / TheClimb::kTileSize);

		if (!getMap()->isFree(nextX, nextY)) return;
		if (units_->collision(nextX, nextY, this)) return;
		
		targetX_ = nextTargetX;
		targetY_ = nextTargetY;

		isMoving_ = true;
	}
	else {

		float step = totalVelocity * dt;
		bool reachedX = (dirX_ == 0) || (std::fabs(targetX_ - posX_) <= step);
		bool reachedY = (dirY_ == 0) || (std::fabs(targetY_ - posY_) <= step);

		if (reachedX && reachedY) {
			setPos(Vector2(targetX_, targetY_));

			if (dm_.x == 0 && dm_.y == 0) {
				isMoving_ = false;
				return;
			}

			float nextTargetX =
				posX_ + static_cast<float>((dm_.x * TheClimb::kTileSize));
			float nextTargetY =
				posY_ + static_cast<float>((dm_.y * TheClimb::kTileSize));

			int nextX = static_cast<int>(nextTargetX / TheClimb::kTileSize);
			int nextY = static_cast<int>(nextTargetY / TheClimb::kTileSize);

			if (!getMap()->isFree(nextX, nextY) ||
				units_->collision(nextX, nextY, this)) {
				isMoving_ = false;
				return;
			}

			targetX_ = nextTargetX;
			targetY_ = nextTargetY;

			dirX_ = dm_.x;
			dirY_ = dm_.y;

		}

		posX_ += dirX_ * step;
		posY_ += dirY_ * step;
	}
}

void Player::Render() {
	float posX = posX_;
	float posY = posY_;
	float size = size_;

	textureDest_ = { posX - 4.f, posY, 24.f, 24.f};

	float x = 0.f;

	if (dirY_ == -1) x += 24.f;

	DrawTexturePro(texture_, {x, 0.f, 24.f, 24.f }, textureDest_, textureOrigin_, 0.0f, WHITE);
}


