#include <stddef.h>
#include <string.h>

#include "raylib.h"

#include "core/simulation.h"

typedef struct Game
{
	Simulation sim;
	Font fonts[1];
	int fps;
	int windowWidth;
	int windowHeight;
} Game;

void Game_Loop(Game *pGame);
void Game_Init(Game *pGame);
void Game_Update(Game *pGame);
void Game_Events(Game *pGame);
void Game_Draw(Game *pGame);
void Game_Close(Game *pGame);

// TODO: Create a `Simulation` struct that takes care of user interaction and
// view of a `Grid` (probably using **Camera2D**)

static void initRaylib(void)
{
	const int windowWidth = 800;
	const int windowHeight = 450;
	const int fps = 60;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(windowWidth, windowHeight, "Sand Simulator");
	SetTargetFPS(fps);

	SetTraceLogLevel(LOG_DEBUG);
}

int main(void)
{
	initRaylib();

	Game game;

	Game_Init(&game);

	Game_Loop(&game);

	Game_Close(&game);

	CloseWindow();

	return 0;
}

void Game_Loop(Game *pGame)
{
	while (!WindowShouldClose())
	{
		Game_Events(pGame);
		Game_Update(pGame);
		Game_Draw(pGame);
	}
}

void Game_Init(Game *pGame)
{
	memset(pGame, 0, sizeof(Game));

	Simulation_Init(&pGame->sim);
}

void Game_Events(Game *pGame)
{
	if (IsWindowResized())
	{
		Simulation_Resize(&pGame->sim);
	}

	Simulation_Click(&pGame->sim);
}

void Game_Update(Game *pGame)
{
	double delta = GetFrameTime();
	Simulation_Update(&pGame->sim, delta);
}

void Game_Draw(Game *pGame)
{
	BeginDrawing();

	Simulation_Draw(&pGame->sim);

	EndDrawing();
}

void Game_Close(Game *pGame)
{
	Simulation_Free(&pGame->sim);
}
