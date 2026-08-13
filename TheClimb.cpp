// TheClimb.cpp: определяет точку входа для приложения.
//

#include "TheClimb.h"

using json = nlohmann::json;

//const int screenW = 1280;
//const int screenH = 720;
int screenW = 1920;
int screenH = 1080;
int targetFps = 144;

float cameraZoom = 6.0f;

const char* PlayerTexture = "resources/player1.png";
float playerVelocity = 32.0f;
float cellSize = 16.0f;

float cameraVel = 8.f;
float cameraZoomVel = 1.f;


std::string settings_path = "resources/settings.json";

static bool load() {
	json settings;
	if (!Util::LoadJson(settings_path, settings)) {
		Util::PrintError("FAILED TO LOAD SETTINGS: json", "MAIN");
		return false;
	}
	if (!Util::Contains(settings, "MAIN", "screen_w")) {
		Util::PrintError("FAILED TO LOAD SETTINGS: screen_w", "MAIN");
		return false;
	}
	if (!Util::Contains(settings, "MAIN", "screen_h")) {
		Util::PrintError("FAILED TO LOAD SETTINGS: screen_h", "MAIN");
		return false;
	}
	if (!Util::Contains(settings, "MAIN", "fps")) {
		Util::PrintError("FAILED TO LOAD SETTINGS: fps", "MAIN");
		return false;
	}
	if (!Util::Contains(settings, "MAIN", "camera_zoom")) {
		Util::PrintError("FAILED TO LOAD SETTINGS: camera_zoom", "MAIN");
		return false;
	}
	if (!Util::Contains(settings, "MAIN", "camera_velocity")) {
		Util::PrintError("FAILED TO LOAD SETTINGS: camera_velocity", "MAIN");
		return false;
	}
	if (!Util::Contains(settings, "MAIN", "camera_velocity_zoom")) {
		Util::PrintError("FAILED TO LOAD SETTINGS: camera_velocity_zoom", "MAIN");
		return false;
	}
	if (!Util::Contains(settings, "MAIN", "player_velocity")) {
		Util::PrintError("FAILED TO LOAD SETTINGS: player_velocity", "MAIN");
		return false;
	}

	screenW = settings.at("screen_w");
	screenH = settings.at("screen_h");

	targetFps = settings.at("fps");

	cameraZoom = settings.at("camera_zoom");
	cameraVel = settings.at("camera_velocity");
	cameraZoomVel = settings.at("camera_velocity_zoom");

	playerVelocity = settings.at("player_velocity");

	return true;
}

int main(void)
{
	if (!load()) return 1;


	#ifdef _DEBUG
		std::cout << Util::Color::Cyan << "INFO " << "--DEBUG MODE--\n" << Util::Color::Reset;
		const bool fullscreen_borderless = 0;
		std::cout << Util::Color::Cyan << "INFO Window init in not fullscreen\n" << Util::Color::Reset;
	#else
		std::cout << Util::Color::Cyan << "INFO " << "--RELEASE MODE--\n" << Util::Color::Reset;
		const bool fullscreen_borderless = 1;
	#endif

	
		



	Game game(screenW, screenH, targetFps, cameraZoom, cameraVel, cameraZoomVel, fullscreen_borderless);
	
	game.Init(1, 1, playerVelocity, game.getTextureManager(), "player1", "resources/player-test-2f.png");

	RenderTexture2D mapGridTexture = LoadRenderTexture(game.getMap().GetSizeX() * TheClimb::kTileSize, game.getMap().GetSizeY() * TheClimb::kTileSize);
	

	BeginTextureMode(mapGridTexture);
		ClearBackground(WHITE);
		game.getMap().RenderGround(game.getTextureManager());
	EndTextureMode();
	//loop

	while (!WindowShouldClose()) {
		if (!IsWindowFocused())
		{
			BeginDrawing();
			ClearBackground(WHITE);
			EndDrawing();
			continue;
		}
		float dt = GetFrameTime();

		

		game.Update(dt);
		BeginDrawing();

			BeginMode2D(game.GetCameraManager().GetCamera());
				ClearBackground(RAYWHITE);
				DrawTextureRec(
					mapGridTexture.texture,
					Rectangle{
						0, 
						0,
						static_cast<float>(mapGridTexture.texture.width),
						static_cast<float>(-mapGridTexture.texture.height)
					},
					Vector2{ 0, 0 },
					WHITE
				);
				game.Render();
			EndMode2D();

			game.getDialogueManager().Render();

		EndDrawing();
	}
	game.Unload();
	CloseWindow();


	return 0;
}
