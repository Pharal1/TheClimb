// CameraManager.cpp

#include "CameraManager.h"
#include "../ent/Unit.h"
#include "../ent/Player.h"
#include "../util.h"

CameraManager::CameraManager(int width, int height, float zoom, float velocity, float zoomVelocity) : zoom_(zoom), camera_(), velocity_(velocity), zoomVelocity_(zoomVelocity) {
	//camera_.offset = { (float)width/2, (float)height/2 };
	camera_.rotation = 0.f;
	camera_.zoom = zoom;
}

void CameraManager::SetTarget(Unit* target) {
	targetUnit_ = target;
	mode_ = CameraTargetMode::eTargetUnit;
}

void CameraManager::SetTarget(Vector2 target) {
	targetXY_ = target;
	mode_ = CameraTargetMode::eTargetCoordinates;
}

void CameraManager::SetTarget() {
	targetUnit_ = player_;
	mode_ = CameraTargetMode::eTargetUnit;
}

void CameraManager::Update(float dt) {
	if (mode_ == CameraTargetMode::eTargetNone) return;
	float targetX = camera_.target.x;
	float targetY = camera_.target.y;
	if (mode_ == CameraTargetMode::eTargetUnit) {
		targetX = targetUnit_->getPosX();
		targetY = targetUnit_->getPosY();
	}
	else if (mode_ == CameraTargetMode::eTargetCoordinates) {
		targetX = targetXY_.x;
		targetY = targetXY_.y;
	}

	camera_.target.x = Lerp(camera_.target.x, targetX, velocity_ * dt);
	camera_.target.y = Lerp(camera_.target.y, targetY, velocity_ * dt);

	camera_.zoom = Lerp(camera_.zoom, zoom_, zoomVelocity_ * dt);
}

void CameraManager::Init(Player* player) {
	if (!player) {
		std::cout << Util::Color::Red << "ERROR CAMERA MANAGER failed to init camera (player is nullptr)\n" << Util::Color::Reset;
	}
	
	camera_.offset = Vector2((float)GetScreenWidth()/2.f, (float)GetScreenHeight()/2.f);
	player_ = player;
}