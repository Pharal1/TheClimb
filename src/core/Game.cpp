#include "Game.h"

Game::Game(int screenW, int screenH, int fps, float zoom) : screenW_(screenW), screenH_(screenH), targetFps_(fps), cameraZoom_(zoom) {
	InitWindow(screenW, screenH, "ZXCLIMB");
	//camera_ = createCamera(player, screenW, screenH);
	
	SetTargetFPS(fps);
}

void Game::Init(Player* player, Map* map) {
	map_ = map;
	player_ = player;
	player_->setNpcList(npc_);
	
	//player_->setMap(map_);

	Camera2D camera = { 0 };

	camera.offset = { screenW_ / 2.0f, screenH_ / 2.0f };
	camera.zoom = cameraZoom_;
	camera.rotation = 0.0f;

	camera.target = { player->getPosX(), player->getPosY() };


	camera_ = camera;
	TextureManager textureManager;
	textureManager_ = textureManager;

	DialogueManager dialogueManager;
	dialogueManager_ = dialogueManager;

	//texture load:

	//textureManager_.load("tileset1", "resources/tileset1.png");

	map_->Load(&textureManager_);
}

void Game::tryInterract() {
	if (player_->isMoving()) return;
	for (Npc* npc : npc_) {
		if (npc->isInterractable()) {
			if (npc->getPosXTile() == player_->getPosXTile() + player_->getDirX() && 
				npc->getPosYTile() == player_->getPosYTile() + player_->getDirY()) 
			{
				std::cout << "Ping\n";
				npc->interract();

				dialogueManager_.startDialogue(npc->getDialogue());
			}	
		}
	}
}

void Game::handleInput() {
	Vector2 deltaPlayer = { 0, 0 };
	bool isRunning = false;
	bool isEPressed = false;
	bool skip = false;
	if (IsKeyDown(KEY_D)) deltaPlayer.x++;
	if (IsKeyDown(KEY_A)) deltaPlayer.x--;
	if (IsKeyDown(KEY_W)) deltaPlayer.y--;
	if (IsKeyDown(KEY_S)) deltaPlayer.y++;

	if (IsKeyDown(KEY_LEFT_SHIFT)) isRunning = true;

	if (IsKeyPressed(KEY_E)) {
		tryInterract();
	}
	if (IsKeyPressed(KEY_SPACE)) {
		skip = true;
	}

	dialogueManager_.skip(skip);
	player_->Input(deltaPlayer, isRunning, isEPressed);
}

void Game::Update(float dt) {

	handleInput();

	for (auto* i : npc_) {
		if (i != nullptr) i->Update(dt);
	}

	if (!dialogueManager_.isActive()) {
		player_->Update(dt);
	} else {
		dialogueManager_.Update(dt);
	}

	camera_.target = { player_->getPosX(), player_->getPosY() };
	camera_.zoom = cameraZoom_;
}

void Game::Render() {
	map_->Render();
	player_->Render();

	for (auto* i : npc_) {
		if (i != nullptr) i->Render();
	}
}
void Game::Unload() {
	textureManager_.unloadAll();
}

void Game::addNpc(Npc* npc) {
	if (npc == nullptr) return;
	npc_.push_back(npc);
	npc->setMap(map_);
	player_->setNpcList(npc_);
}

bool Game::isTileFree(int x, int y) const {
	if (!map_->isFree(x, y)) return false;

	for (Npc* npc : npc_) {
		if (npc->getPosXTile() == x || npc->getPosYTile() == y) return false;
	}

	return true;
}