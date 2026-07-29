// TheClimb.cpp: определяет точку входа для приложения.
//

#include "TheClimb.h"

//const int screenW = 1280;
//const int screenH = 720;
const int screenW = 1920;
const int screenH = 1080;
const int targetFps = 144;

float cameraZoom = 6.0f;

const char* PlayerTexture = "resources/player1.png";
const float playerVelocity = 32.0f;
const float cellSize = 16.0f;

const float cameraVel = 16.f;
const float cameraZoomVel = 1.f;
const bool fullscreen_borderless = false;


int main(void)
{
	


	Game game(screenW, screenH, targetFps, cameraZoom, cameraVel, cameraZoomVel, fullscreen_borderless);
	
	game.Init(1, 1, playerVelocity, cellSize, game.getTextureManager(), "player1", "resources/player3.png");

	game.getUnitManager().addUnit<Npc>(4, 3, 10, 16, game.getTextureManager(), TextureData{ "npc1", "resources/npc1.png" }, 1);

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
			ClearBackground(BLACK);
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
				//DrawTexture(textr1, 0, 0, WHITE);
				DrawRectangle(0, 0, 4, 4, RED);
				game.Render();
				//DrawTexture(textr, 0, 0, WHITE);
			EndMode2D();

			game.getDialogueManager().Render();

		EndDrawing();
	}
	//UnloadTexture(textr1);
	game.Unload();
	CloseWindow();


	return 0;
}
