#include "raylib.h"

#include <stdbool.h>

#include "scenes/manager.h"
#include "scenes/scenes/game.h"
#include "scenes/scenes/pause.h"

void initRaylib(void);

int main(int argc, char *argv[])
{
	initRaylib();

	// NOTE: The `SceneManager_Init` initialize
	// the g_SceneManager global variable.
	SceneManager_Init();

	SceneManager_Register(Game_Scene);
	SceneManager_Register(Pause_Scene);

	SceneManager_Switch(GAME_NAME);

	SceneManager_Loop();

	SceneManager_Free();

	CloseWindow();

	return 0;
}

void initRaylib(void)
{
#if defined(DEBUG)
	SetTraceLogLevel(LOG_DEBUG);
#else
	SetTraceLogLevel(LOG_ERROR);
#endif

	const int windowWidth = 1024;
	const int windowHeight = 560;
	const int fps = 60;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(windowWidth, windowHeight, "Sand Simulator");
	SetTargetFPS(fps);
}
