// Player.h
#ifndef PLAYER_H_
#define PLAYER_H_

#include "raylib.h"
#include "math.h"
#include "../world/Map.h"
#include <iostream>
#include "../manager/TextureManager.h"

class Player {
public:
	Player(int posXTile, int posYTile, float velocity, float size);
	void setMap(Map* map) { map_ = map; }
	void Update(float dt, Vector2 dm, bool isRunning);
	void Render();
	void Load(TextureManager textureManager);
	Texture2D getTexture() const { return texture_; }
	float getPosX() const { return posX_; }
	float getPosY() const { return posY_; }

	void setRunningMultiplier(float value) { velocityRunningMultiplier = value; }
	void setPosTile(int x, int y); // NO ISFREE() CHECK
	void setPosTileX(int x);
	void setPosTileY(int y);
private:
	float posX_;
	float posY_;
	int posXTile_;
	int posYTile_;
	int targetTileX_;
	int targetTileY_;
	int dirX_ = 0;
	int dirY_ = 0;

	bool isMoving_ = false;
	Texture2D texture_{};
	float velocity_;
	float velocityRunningMultiplier = 1.5f;
	//float velocity_diag;
	float size_;

	Rectangle textureSource{};
	Rectangle textureDest{};
	Vector2 textureOrigin{};

	Map* map_ = nullptr;
};

#endif