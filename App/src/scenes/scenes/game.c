#include "game.h"

#include <stdlib.h>

#include "raygui.h"
#include "raylib.h"
#include "raymath.h"

#include "scenes/manager.h"
#include "scenes/scenes/pause.h"
#include "simulation/sim.h"
#include "utils/free.h"

#include "gui/game/brush.h"
#include "gui/themes/catppuccin_mocha.h"

void Game_Init(void *data)
{
	Game *pGame = (Game *)data;

	const int defaultWidth = 512;
	const int defaultHeight = 280;

	Sim_Init(&pGame->sim, defaultWidth, defaultHeight);

	Theme_Init(&pGame->theme, &Theme_CatpuccinMocha);

	SimRenderer_Init(&pGame->simRenderer, &pGame->sim);

	GameUi_Init(&pGame->ui);
}

void Game_Free(void *data)
{
	Game *pGame = (Game *)data;

	Sim_Free(&pGame->sim);
	SimRenderer_Free(&pGame->simRenderer);

	FREE(pGame);
}

void Game_Update(void *data)
{
	Game *pGame = (Game *)data;

	Game_Keyboard(pGame);

	Game_Mouse(pGame);

	Sim_Update(&pGame->sim, GetFrameTime());
}

void Game_Draw(void *data)
{
	Game *pGame = (Game *)data;

	SimRenderer_Render(&pGame->simRenderer, &pGame->sim, &pGame->theme);

	Brush_Draw(NULL);
	GameUi_Draw(&pGame->ui, &pGame->theme);

	// TraceLog(LOG_DEBUG, "Click:\t%d", clickCount);
	// TraceLog(LOG_DEBUG, "Sim:\t%d", pGame->sim.sandCount);
}

void Game_Keyboard(Game *pGame)
{
	if (IsKeyPressed(KEY_P))
	{
		SetTargetFPS(24);
		SceneManager_Switch(PAUSE_NAME);
	}

	if (IsKeyPressed(KEY_ONE))
	{
		pGame->ui.elements.current = ELEMENT_SAND;
	}
	else if (IsKeyPressed(KEY_TWO))
	{
		pGame->ui.elements.current = ELEMENT_WATER;
	}
	else if (IsKeyPressed(KEY_THREE))
	{
		pGame->ui.elements.current = ELEMENT_STONE;
	}
	else if (IsKeyPressed(KEY_FOUR))
	{
		pGame->ui.elements.current = ELEMENT_GLASS;
	}
	else if (IsKeyPressed(KEY_FIVE))
	{
		pGame->ui.elements.current = ELEMENT_LAVA;
	}
	else if (IsKeyPressed(KEY_SIX))
	{
		pGame->ui.elements.current = ELEMENT_EMPTY;
	}
	else if (IsKeyPressed(KEY_SEVEN))
	{
		pGame->ui.elements.current = ELEMENT_EMPTY;
	}
	else if (IsKeyPressed(KEY_EIGHT))
	{
		pGame->ui.elements.current = ELEMENT_EMPTY;
	}
	else if (IsKeyPressed(KEY_NINE))
	{
		pGame->ui.elements.current = ELEMENT_EMPTY;
	}
	else if (IsKeyPressed(KEY_ZERO))
	{
		pGame->ui.elements.current = ELEMENT_EMPTY;
	}
}

void Game_Mouse(Game *pGame)
{
	Rectangle *pView = &pGame->simRenderer.viewPort;
	float cellSize = (float)pGame->simRenderer.cellSize;

	if (!IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		return;

	Vector2 mouse = GetMousePosition();

	if (!CheckCollisionPointRec(mouse, *pView))
		return;

	Vector2 mouseInView = Vector2Subtract(mouse, (Vector2){pView->x, pView->y});

	mouseInView.x /= cellSize;
	mouseInView.y /= cellSize;

	mouseInView.x = roundf(mouseInView.x);
	mouseInView.y = roundf(mouseInView.y);

	int index = Sim_GetIndex((int)mouseInView.y, (int)mouseInView.x, pGame->sim.width);
	if (!Sim_IsIndexValid(&pGame->sim, index))
	{
		return;
	}

	// pGame->sim.current[index].id = pGame->ui.elements.current;
	Sim_UserAddElement(&pGame->sim, index, pGame->ui.elements.current);
}

Scene Game_Scene(void)
{
	void *data = malloc(sizeof(Game));

	Scene scene = {
	    .Init = Game_Init,
	    .Free = Game_Free,
	    .Update = Game_Update,
	    .Draw = Game_Draw,
	    .pData = data,
	    .name = GAME_NAME,
	};

	return scene;
}
