// TheClimb.cpp: определяет точку входа для приложения.
//

#include "TheClimb.h"

const int screenW = 1280;
const int screenH = 720;
const int targetFps = 144;

float cameraZoom = 6.0f;

const char* PlayerTexture = "resources/player1.png";
const float playerVelocity = 32.0f;
const float cellSize = 16.0f;

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

const std::vector<std::string> map3m{
	"1111111111111111111111111111",
	"1000000000000000000000000001",
	"1000000000000000000000000001",
	"1000000000000000000000000001",
	"1000000000000000000000000001",
	"1000000000000000000000000001",
	"1000000000000000000000000001",
	"1000000000000000000000000001"
};

MapData test_map(map3m, cellSize);

int main(void)
{
	//initilisation
	Game game(screenW, screenH, targetFps, cameraZoom);
	Map map(test_map);
	Player player(1, 1, playerVelocity, cellSize, game.getTextureManager(), "player1", "resources/player3.png");
	player.setMap(&map);
	game.Init(&player, &map);

	Npc npc1(4, 4, 10, 16, game.getTextureManager(), "npc1", "resources/npc1.png", 1);
	npc1.setDialogue({ "zxcursed", {"im zxcuesed", "coil coil coil"} });
	game.addNpc(&npc1);

	initTileSet();
	//Texture2D textr = LoadTexture("resources/player3.png");
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
