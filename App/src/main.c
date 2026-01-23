#include <stddef.h>

#include "raylib.h"

#include "scenes/manager.h"
#include "scenes/scenes/game.h"
#include "scenes/scenes/pause.h"

#include "scenes_id.h"

void SceneManager_Loop(SManager *pMan);

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

	SManager manager;

	SceneManager_Init(&manager, SCENE_TOTAL);
	SceneManager_Add(&manager, Game_Scene, SCENE_GAME);
	SceneManager_Add(&manager, Pause_Scene, SCENE_PAUSE);

	SceneManager_Switch(&manager, SCENE_GAME);

	SceneManager_Loop(&manager);

	SceneManager_Free(&manager);

	CloseWindow();

	return 0;
}
