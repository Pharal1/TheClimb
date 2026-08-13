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
	dialogueManager_(screenW, screenH, cameraManager_)
{
	std::string title = "ZXCLIBE";
#ifdef _DEBUG
		title += " --DEBUG";
#endif
	if (fullscreen_borderless) {
		SetConfigFlags(FLAG_WINDOW_UNDECORATED);
		InitWindow(screenW, screenH, title.c_str());

		SetWindowPosition(0, 0);
		SetWindowSize(GetMonitorWidth(0), GetMonitorHeight(0));
	}
	else {
		InitWindow(screenW, screenH, title.c_str());
	}
	SetTargetFPS(fps);
	
	
}

void Game::Init(int posXTile, int posYTile, float velocity, TextureManager& manager, const char* textureID, const char* texturePath) {
	TextureManager textureManager;
	textureManager_ = textureManager;
	std::string font = "resources/font/PressStart2P-Regular.ttf";
	textureManager_.LoadFont(font);
	renderer_.setTextureManager(&textureManager_);
	map_.Load("resources/maps/map1.json", textureManager_, unitManager_, dialogueManager_);

	player_ = &unitManager_.CreatePlayer(posXTile, posYTile, velocity, manager, TextureData{ textureID, texturePath });

	player_->setMap(&map_);
	cameraManager_.SetTarget(player_);
	dialogueManager_.Load(textureManager_);
	
	cameraManager_.Init(player_);
}

void Game::tryInteract() {
	if (player_->isMoving()) return;
	auto* unit = unitManager_.getInteractableAt(static_cast<int>(player_->getPosX() / static_cast<float>(TheClimb::kTileSize)) + player_->getDirX(), static_cast<int>(player_->getPosY() / static_cast<float>(TheClimb::kTileSize)) + player_->getDirY());
	if (unit) {
		std::cout << "Ping\n";
		unit->Interact(*player_);
		//dialogueManager_.startDialogue(static_cast<Npc*>(unit)->GetDialogue());	
		
	}
}

void Game::handleInput() {
	Vector2 deltaPlayer = { 0, 0 };
	Vector2 deltaGui = { 0, 0 };
	bool isRunning = false;
	bool isEPressed = false;
	bool skip = false;

	if      (IsKeyDown(KEY_A)) deltaPlayer.x--;
	else if (IsKeyDown(KEY_D)) deltaPlayer.x++;
	else if (IsKeyDown(KEY_W)) deltaPlayer.y--;
	else if (IsKeyDown(KEY_S)) deltaPlayer.y++;

	if      (IsKeyPressed(KEY_LEFT))  deltaGui.x--;
	else if (IsKeyPressed(KEY_RIGHT)) deltaGui.x++;
	else if (IsKeyPressed(KEY_UP))    deltaGui.y--;
	else if (IsKeyPressed(KEY_DOWN))  deltaGui.y++;
	else if (IsKeyPressed(KEY_A))     deltaGui.x--;
	else if (IsKeyPressed(KEY_D))     deltaGui.x++;
	else if (IsKeyPressed(KEY_W))     deltaGui.y--;
	else if (IsKeyPressed(KEY_S))     deltaGui.y++;


	if (IsKeyDown(KEY_LEFT_SHIFT)) isRunning = true;

	if (IsKeyPressed(KEY_E)) {
		isEPressed = true;
		//if (dialogueManager_.isActive()) skip = true;
	}
	if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER)) {
		skip = true;
	}

	Util::HandleInput handleInputData{ isRunning, isEPressed, skip + isEPressed, deltaPlayer, deltaGui };

	dialogueManager_.Input(handleInputData);

	if (!dialogueManager_.isActive()) {
		player_->Input(handleInputData);
	}
	if (isEPressed) {
		if (!dialogueManager_.isActive()) tryInteract();
	}


	if (IsKeyPressed(KEY_F11)) {
		Util::debug = !Util::debug;
		Util::debug ? std::cout << Util::Color::Cyan << "Debug: ON\n" << Util::Color::Reset : std::cout << Util::Color::Cyan << "Debug: OFF\n" << Util::Color::Reset;
	}
}

void Game::Update(float dt) {

	unitManager_.Update(dt);
	dialogueManager_.Update(dt);
	handleInput();
	
	
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