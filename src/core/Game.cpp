#include "Game.h"

Game::Game(int screenW, int screenH, int fps, float zoom) : screenW_(screenW), screenH_(screenH), targetFps_(fps), cameraZoom_(zoom) {
	InitWindow(screenW, screenH, "ZXCLIMB");
	//camera_ = createCamera(player, screenW, screenH);
	
	SetTargetFPS(fps);
}

void Game::Init(Player* player, Map* map) {
	player_ = player;
	map_ = map;
	
	//player_->setMap(map_);

	Camera2D camera = { 0 };

	camera.offset = { screenW_ / 2.0f, screenH_ / 2.0f };
	camera.zoom = cameraZoom_;
	camera.rotation = 0.0f;

	camera.target = { player->getPosX(), player->getPosY() };


	camera_ = camera;
	TextureManager textureManager;
	textureManager_ = textureManager;

	//texture load:

	//textureManager_.load("tileset1", "resources/tileset1.png");

	map_->Load(textureManager_);
}

void Game::Update(float dt) {

	Vector2 deltaPlayer = { 0, 0 };
	bool isRunning = false;
	if (IsKeyDown(KEY_D)) deltaPlayer.x++;
	if (IsKeyDown(KEY_A)) deltaPlayer.x--;
	if (IsKeyDown(KEY_W)) deltaPlayer.y--;
	if (IsKeyDown(KEY_S)) deltaPlayer.y++;

	if (IsKeyDown(KEY_LEFT_SHIFT)) isRunning = true;

	player_->Update(dt, deltaPlayer, isRunning);
	camera_.target = { player_->getPosX(), player_->getPosY() };
	camera_.zoom = cameraZoom_;
}

void Game::Render() {
	map_->Render();
	player_->Render();
}
void Game::Unload() {
	textureManager_.unloadAll();
}