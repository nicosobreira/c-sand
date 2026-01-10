#include <stddef.h>

#include "raylib.h"

#include "simulation/grid.h"

typedef struct Game
{
	Grid sim;
} Game;

void Game_Loop(Game *pGame);
void Game_Init(Game *pGame);
void Game_Update(Game *pGame);
void Game_Events(Game *pGame);
void Game_Draw(Game *pGame);
void Game_Close(Game *pGame);

// TODO: Create a `Simulation` struct that takes care of user interaction and
// view of a `Grid` (probably using **Camera2D**)

int main(void)
{
	InitWindow(800, 450, "Sand Sim");
	SetTargetFPS(60);

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
	const int width = 100;
	const int height = 100;
	const int cellSize = 4;
	Grid_Init(&pGame->sim, width, height, cellSize);
}

void Game_Events(Game *pGame)
{
	(void)pGame;
}

void Game_Update(Game *pGame)
{
	double delta = GetFrameTime();
	Grid_Update(&pGame->sim, delta);
}

void Game_Draw(Game *pGame)
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	Grid_Render(&pGame->sim);

	DrawFPS(0, 0);

	EndDrawing();
}

void Game_Close(Game *pGame)
{
	Grid_Free(&pGame->sim);
}
