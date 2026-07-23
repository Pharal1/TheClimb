#include "Game.h"

Game::Game(int screenW, int screenH, int fps, float zoom) : screenW_(screenW), screenH_(screenH), targetFps_(fps), cameraZoom_(zoom), dialogueManager_(screenW, screenH), renderer_(), unitManager_(), map_() {
	InitWindow(screenW, screenH, "ZXCLIMB");
	SetTargetFPS(fps);
}

void Game::Init(Player* player) {
	TextureManager textureManager;
	textureManager_ = textureManager;
	renderer_.setTextureManager(&textureManager_);
	//map_.setTextureManager(&textureManager_);

	player_ = player;
	player_->setUnitManager(&unitManager_);
	//player_->setNpcList(npc_);
	
	player_->setMap(&map_);

	Camera2D camera = { 0 };

	camera.offset = { screenW_ / 2.0f, screenH_ / 2.0f };
	camera.zoom = cameraZoom_;
	camera.rotation = 0.0f;

	camera.target = { player->getPosX(), player->getPosY() };

	

	camera_ = camera;
	
	map_.Load("resources/maps/map1.json", textureManager_);
	dialogueManager_.Load(textureManager_);
}

void Game::tryInteract() {
	if (player_->isMoving()) return;
	auto* unit = unitManager_.getInteractableAt(player_->getPosXTile() + player_->getDirX(), player_->getPosYTile() + player_->getDirY());
	if (unit) {
		std::cout << "Ping\n";
		unit->Interact(*player_);

		//dialogueManager_.startDialogue(unit->getDialogue());	
		
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
		tryInteract();
	}
	if (IsKeyPressed(KEY_SPACE)) {
		skip = true;
	}

	dialogueManager_.skip(skip);
	player_->Input(deltaPlayer, isRunning, isEPressed);
}

void Game::Update(float dt) {

	handleInput();

	if (!dialogueManager_.isActive()) {
		player_->Update(dt);
	} else {
		dialogueManager_.Update(dt);
	}

	camera_.target = { player_->getPosX(), player_->getPosY() };
	camera_.zoom = cameraZoom_;
}

void Game::Render() {
	renderer_.Render(map_, unitManager_, dialogueManager_);
}
void Game::Unload() {
	textureManager_.unloadAll();
}

bool Game::isTileFree(int x, int y) const {
	if (!map_.isFree(x, y)) return false;

	if (unitManager_.collision(x, y)) return false;

	return true;
}