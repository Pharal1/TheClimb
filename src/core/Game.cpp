#include "Game.h"

Game::Game(
	int screenW,
	int screenH,
	int fps,
	float zoom,
	float cameraVelocity,
	float cameraVelocityZoom,
	bool fullscreen_borderless
) :
	screenW_(screenW),
	screenH_(screenH),
	targetFps_(fps),
	renderer_(),
	map_(),
	cameraManager_(GetScreenWidth(), GetScreenHeight(), zoom, cameraVelocity, cameraVelocityZoom),
	unitManager_(),
	dialogueManager_(screenW, screenH)
{
	if (fullscreen_borderless) {
		SetConfigFlags(FLAG_WINDOW_UNDECORATED);
		InitWindow(screenW, screenH, "ZXCLIMB");

		SetWindowPosition(0, 0);
		SetWindowSize(GetMonitorWidth(0), GetMonitorHeight(0));
	}
	else {
		InitWindow(screenW, screenH, "ZXCLIMB");
	}
	SetTargetFPS(fps);
	
	
}

void Game::Init(int posXTile, int posYTile, float velocity, float size, TextureManager& manager, const char* textureID, const char* texturePath) {
	TextureManager textureManager;
	textureManager_ = textureManager;
	renderer_.setTextureManager(&textureManager_);
	map_.Load("resources/maps/map1.json", textureManager_, unitManager_);
	//map_.setTextureManager(&textureManager_);

	player_ = &unitManager_.CreatePlayer(posXTile, posYTile, velocity, size, manager, TextureData{ textureID, texturePath });
	//player_->setNpcList(npc_);

	player_->setMap(&map_);
	cameraManager_.SetTarget(player_);
	dialogueManager_.Load(textureManager_);
	std::cout << (float)GetScreenWidth() << (float)GetScreenHeight() << std::endl << cameraManager_.GetCamera().offset.x << cameraManager_.GetCamera().offset.y << std::endl;
	cameraManager_.Init();

	//renderer_.PreRender(map_);
}

void Game::tryInteract() {
	if (player_->isMoving()) return;
	auto* unit = unitManager_.getInteractableAt(static_cast<int>(player_->getPosX() / static_cast<float>(TheClimb::kTileSize)) + player_->getDirX(), static_cast<int>(player_->getPosY() / static_cast<float>(TheClimb::kTileSize)) + player_->getDirY());
	if (unit) {
		std::cout << "Ping\n";
		unit->Interact(*player_);
		Dialogue dialogue("cursed", { "hello,", "yopta" });
		static_cast<Npc*>(unit)->setDialogue(dialogue);
		dialogueManager_.startDialogue(static_cast<Npc*>(unit)->getDialogue());	
		
	}
}

void Game::handleInput() {
	Vector2 deltaPlayer = { 0, 0 };
	bool isRunning = false;
	bool isEPressed = false;
	bool skip = false;
	if (IsKeyDown(KEY_A)) deltaPlayer.x--;
	else if (IsKeyDown(KEY_D)) deltaPlayer.x++;
	else if (IsKeyDown(KEY_W)) deltaPlayer.y--;
	else if (IsKeyDown(KEY_S)) deltaPlayer.y++;

	if (IsKeyDown(KEY_LEFT_SHIFT)) isRunning = true;

	if (IsKeyPressed(KEY_E)) {
		tryInteract();
	}
	if (IsKeyPressed(KEY_SPACE)) {
		skip = true;
		std::cout << "SPACE pressed\n";
	}

	dialogueManager_.skip(skip);
	player_->Input(deltaPlayer, isRunning, isEPressed);
}

void Game::Update(float dt) {

	handleInput();

	unitManager_.Update(dt);
	dialogueManager_.Update(dt);
	/*
	if (!dialogueManager_.isActive()) {
		player_->Update(dt);
	} else {
		
	}
	*/
	//camera_.target = { player_->getPosX(), player_->getPosY() };
	//camera_.zoom = cameraZoom_;
	cameraManager_.Update(dt);
}

void Game::Render() {
	renderer_.Render(map_, unitManager_, dialogueManager_, *player_, cameraManager_);
}
void Game::Unload() {
	textureManager_.unloadAll();
}

bool Game::isTileFree(int x, int y) const {
	if (!map_.isFree(x, y)) return false;

	//if (unitManager_.collision(x, y)) return false;

	return true;
}

void Game::PreRenderer() {
	renderer_.PreRender(map_);
}