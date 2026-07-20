#ifndef GAME_H_
#define GAME_H_

#include "raylib.h"
#include "../ent/Player.h"
#include "../ent/Npc.h"
#include "../world/Map.h"
#include "../manager/TextureManager.h"
#include "../manager/dialogue/DialogueManager.h"
#include <memory>


class Game {
public:
	Game(int screenW, int screenH, int fps, float zoom);
	
	void Init(Player* player, Map* map);
	void addNpc(Npc* npc);
	void Update(float dt);
	void Render(/*TextureManager textureManager*/);
	void Unload();
	int getW() const { return screenW_; }
	int getH() const { return screenH_; }
	Map* getMap() const { return map_; }
	Camera2D getCamera() const { return camera_; }
	TextureManager& getTextureManager() { return textureManager_; }
	DialogueManager& getDialogueManager() { return dialogueManager_; }

	bool isTileFree(int x, int y) const;

	
private:
	Map* map_ = nullptr;
	Player* player_ = nullptr;
	Camera2D camera_{};
	TextureManager textureManager_{};

	DialogueManager dialogueManager_;
	std::vector<Npc*> npc_;

	void tryInterract();
	void handleInput();

	const int screenW_;
	const int screenH_;
	const int targetFps_;
	float cameraZoom_;
};

#endif // !GAME_H_
