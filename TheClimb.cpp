// TheClimb.cpp: определяет точку входа для приложения.
//

#include "TheClimb.h"

const int screenW = 1280;
const int screenH = 720;
const int targetFps = 144;

float cameraZoom = 16.0f;

const char* PlayerTexture = "resources/player1.png";
const float playerVelocity = 18.0f;
const float cellSize = 3.0f;


/*
'0' = floor
'1' = wall
'2' = water



maps:  */
const std::vector<std::string> map1{
	"11111",
	"10001",
	"10001",
	"10001",
	"11111"
};

const std::vector<std::string> map2{
	"111111111",
	"100000001",
	"102202201",
	"102202201",
	"100000001",
	"102202201",
	"102202201",
	"100000001",
	"111111111"
};

const std::vector<std::string> map3{
	"1111111111111111111111111111",
	"1000000000000000000000000001",
	"1000000000000000000000000001",
	"1000000000000000000000000001",
	"1000000000000000000000000001",
	"1000000000000000000000000001",
	"1000000000000000000000000001",
	"1000000000000000000000000001",
	"2222222222222222222222222222",
	"2222222222222222222222222222",
	"2222222222222222222222222222",
	"2222222222222222222222222222"
};

MapData test_map(map3, 3);

int main(void)
{
	//initilisation
	Game game(screenW, screenH, targetFps, cameraZoom);
	Map map(test_map);
	Player player(1, 1, PlayerTexture, playerVelocity, cellSize);
	player.setMap(&map);
	game.Init(&player, &map);
	initTileSet();
	//Texture2D textr1 = LoadTexture(PlayerTexture);

	//loop
	while (!WindowShouldClose()) {
		float dt = GetFrameTime();

		game.Update(dt);
		BeginDrawing();
		BeginMode2D(game.getCamera());
		ClearBackground(RAYWHITE);
		//DrawTexture(textr1, 0, 0, WHITE);
		DrawRectangle(0, 0, 4, 4, RED);
		map.Render();
		player.Render();

		EndMode2D();
		EndDrawing();
	}
	//UnloadTexture(textr1);

	CloseWindow();

	return 0;
}
