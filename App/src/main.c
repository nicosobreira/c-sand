#include <stddef.h>
#include <string.h>

#include "clay.h"
#include "raylib.h"

#include "sim/simulation.h"

// TODO: Implement grid.updatedIndexes on Renderer

typedef struct Game
{
	Simulation sim;
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

static void initRaylib(void)
{
	const int windowWidth = 1024;
	const int windowHeight = 560;
	const int fps = 60;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(windowWidth, windowHeight, "Sand Simulator");
	SetTargetFPS(fps);

	SetTraceLogLevel(LOG_DEBUG);
}

static void HandleClayErrors(Clay_ErrorData errorData)
{
	TraceLog(LOG_ERROR, "%s", errorData.errorText.chars);
	CloseWindow();
	exit(EXIT_FAILURE);
}

static Clay_Dimensions MeasureTextClay(Clay_StringSlice text, Clay_TextElementConfig *config, void *userData)
{
	return (Clay_Dimensions){.width = MeasureText(text.chars, config->fontSize), .height = config->fontSize};
}

static void initClay(void)
{
	uint64_t totalMemorySize = Clay_MinMemorySize();
	Clay_Arena arena = Clay_CreateArenaWithCapacityAndMemory(totalMemorySize, malloc(totalMemorySize));

	Clay_Initialize(
	    arena, (Clay_Dimensions){GetScreenWidth(), GetScreenHeight()}, (Clay_ErrorHandler){HandleClayErrors}
	);

	Clay_SetMeasureTextFunction(MeasureTextClay, 0);
}

int main(void)
{
	initRaylib();
	initClay();

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
	Simulation_Click(&pGame->sim);
}

void Game_Update(Game *pGame)
{
	double delta = GetFrameTime();
	Simulation_Update(&pGame->sim, delta);
}

void Game_Draw(Game *pGame)
{
	if (IsWindowResized())
	{
		Simulation_Resize(&pGame->sim);
	}

	Rectangle *pView = &pGame->sim.gridRenderer.viewPort;

	const Clay_Dimensions dimensions = {
	    pView->width + pView->x,
	    pView->height + pView->y,
	};

	Clay_SetLayoutDimensions(dimensions);
	Clay_SetPointerState((Clay_Vector2){GetMouseX(), GetMouseY()}, IsMouseButtonDown(0));

	BeginDrawing();

	Simulation_Draw(&pGame->sim);

	EndDrawing();
}

void Game_Close(Game *pGame)
{
	Simulation_Free(&pGame->sim);
}
