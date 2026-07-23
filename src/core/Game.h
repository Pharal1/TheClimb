#ifndef GAME_H_
#define GAME_H_

#include <memory>
#include "raylib.h"

#include "../ent/Player.h"
#include "../ent/Npc.h"
#include "../world/Map.h"
#include "../manager/TextureManager.h"
#include "../manager/dialogue/DialogueManager.h"
#include "../manager/UnitManager.h"
#include "../manager/renderer.h"


class Game {
public:
	Game(int screenW, int screenH, int fps, float zoom);
	
	void Init(Player* player);
	void Update(float dt);
	void Render(/*TextureManager textureManager*/);
	void Unload();
	int getW() const { return screenW_; }
	int getH() const { return screenH_; }
	Map& const getMap() { return map_; }
	Camera2D getCamera() const { return camera_; }
	TextureManager& getTextureManager() { return textureManager_; }
	DialogueManager& getDialogueManager() { return dialogueManager_; }

	bool isTileFree(int x, int y) const;

	UnitManager& getUnitManager() { return unitManager_; } //DELETE THIS
	
private:
	Map map_;
	Player* player_ = nullptr;
	Camera2D camera_{};
	TextureManager textureManager_{};

	DialogueManager dialogueManager_;
	Renderer renderer_;
	UnitManager unitManager_;

	void tryInteract();
	void handleInput();

	const int screenW_;
	const int screenH_;
	const int targetFps_;
	float cameraZoom_;
};

#endif // !GAME_H_
