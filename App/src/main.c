#include <stddef.h>

#include "raylib.h"

#include "scenes/manager.h"
#include "scenes/scenes/game.h"
#include "scenes/scenes/pause.h"

#include "scenes_id.h"

static void initRaylib(void)
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

int main(void)
{
	initRaylib();

	// NOTE: The `SceneManager_Init` initialize
	// the g_SceneManager global variable.
	SceneManager_Init(SCENE_TOTAL);

	SceneManager_Add(Game_Scene, SCENE_GAME);
	SceneManager_Add(Pause_Scene, SCENE_PAUSE);

	SceneManager_Switch(SCENE_GAME);

	SceneManager_Loop();

	SceneManager_Free();

	CloseWindow();

	return 0;
}
