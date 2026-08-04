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
#include "../manager/CameraManager.h"

enum class GameStatus {
	eDefault,
	eDialogue
};



class Game {
public:
	Game(int screenW, int screenH, int fps, float zoom, float cameraVelocity, float cameraVelocityZoom, bool fullscreen_borderless);
	
	void Init(int posXTile, int posYTile, float velocity, float size, TextureManager& manager, const char* textureID, const char* texturePath);
	void Update(float dt);
	void Render(/*TextureManager textureManager*/);
	void Unload();
	int GetW() const { return screenW_; }
	int getH() const { return screenH_; }
	Map& const getMap() { return map_; }
	CameraManager GetCameraManager() const { return cameraManager_; }
	TextureManager& getTextureManager() { return textureManager_; }
	DialogueManager& getDialogueManager() { return dialogueManager_; }
	void PreRenderer();

	bool isTileFree(int x, int y) const;

	UnitManager& getUnitManager() { return unitManager_; } //DELETE THIS
	
private:
	Map map_;
	Player* player_ = nullptr;
	CameraManager cameraManager_;
	TextureManager textureManager_{};

	DialogueManager dialogueManager_;
	Renderer renderer_;
	UnitManager unitManager_;

	void tryInteract();
	void handleInput();

	const int screenW_;
	const int screenH_;
	const int targetFps_;
	



};

#endif // !GAME_H_
