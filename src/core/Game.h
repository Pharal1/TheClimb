#ifndef GAME_H_
#define GAME_H_

#include "raylib.h"
#include "../ent/Player.h"
#include "../world/Map.h"
#include "../manager/TextureManager.h"

class Game {
public:
	Game(int screenW, int screenH, int fps, float zoom);
	
	void Init(Player* player, Map* map);
	void Update(float dt);
	void Render(/*TextureManager textureManager*/);
	void Unload();
	int getW() const { return screenW_; }
	int getH() const { return screenH_; }
	Map* getMap() const { return map_; }
	Camera2D getCamera() const { return camera_; }
private:
	Map* map_ = nullptr;
	Player* player_ = nullptr;
	Camera2D camera_{};
	TextureManager textureManager_{};

	const int screenW_;
	const int screenH_;
	const int targetFps_;
	float cameraZoom_;
};

#endif // !GAME_H_
