// CameraManager.h

#pragma once

#include <raylib.h>
#include <raymath.h>


class Unit;
class Player;

enum class CameraTargetMode {
	eTargetNone,
	eTargetUnit,
	eTargetCoordinates
};

class CameraManager {
public:
	CameraManager(int width, int height, float zoom, float velocity, float zoomVelocity);
	void Update(float dt);
	void Init(Player* player);

	void SetMode(CameraTargetMode mode) { mode_ = mode; }
	void SetZoom(float zoom) { zoom_ = zoom; }
	void SetTarget(Unit* target);
	void SetTarget(Vector2 target);
	//Sets target to the player 
	//from CameraManager::Init()
	void SetTarget();

	Camera2D GetCamera() const { return camera_; }
private:
	Camera2D camera_;

	CameraTargetMode mode_ = CameraTargetMode::eTargetNone;
	Unit* targetUnit_ = nullptr;
	Vector2 targetXY_{ 0.f, 0.f };
	float zoom_;
	float velocity_;
	float zoomVelocity_;
	Player* player_ = nullptr;
};