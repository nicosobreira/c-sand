#include "pause.h"

#include <stddef.h>

#include "scenes/manager.h"
#include "scenes/scenes/game.h"
#include "scenes_id.h"

#include "raylib.h"

void Pause_Func(void *data)
{
	(void)data;
}

void Pause_Update(void *data)
{
	(void)data;

	if (IsKeyPressed(KEY_P))
	{
		SetTargetFPS(60);
		SceneManager_Switch(GAME_NAME);
	}
}

void Pause_Draw(void *data)
{
	(void)data;

	// clang-format off
	DrawRectangle(
	    0,
		0,
		GetScreenWidth(),
		GetScreenHeight(),
		Fade(BLACK, 0.5f)
	);
	// clang-format on

	const char *text = "Paused";
	const int fontSize = 40;
	const int textWidth = MeasureText(text, fontSize);

	// clang-format off
	DrawText(
		text,
		(GetScreenWidth() - textWidth) / 2,
		(GetScreenHeight() - fontSize) / 2,
		fontSize,
		WHITE
	);
	// clang-format on
}

Scene Pause_Scene(void)
{
	void *data = NULL;

	Scene scene = {
	    .Init = Pause_Func,
	    .Free = Pause_Func,
	    .Update = Pause_Update,
	    .Draw = Pause_Draw,
	    .pData = data,
	    .name = PAUSE_NAME,
	};

	return scene;
}
