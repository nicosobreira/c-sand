#include "game.h"

#include <math.h>
#include <string.h>

#include "clay.h"
#include "raylib.h"
#include "raymath.h"

#include "simulation/sim.h"

#include "ui/themes/catppuccin_mocha.h"

void Game_Init(void *data)
{
	Game *pGame = (Game *)data;

	memset(pGame, 0, sizeof(Game));

	const int defaultWidth = 512;
	const int defaultHeight = 280;

	Sim_Init(&pGame->sim, defaultWidth, defaultHeight);

	Theme_Init(&pGame->theme, &Theme_CatpuccinMocha);

	SimRenderer_Init(&pGame->simRenderer, &pGame->sim);
}

void Game_Free(void *data)
{
	Game *pGame = (Game *)data;

	Sim_Free(&pGame->sim);

	free(pGame);

	memset(pGame, 0, sizeof(Game));
}

void Game_Update(void *data)
{
	Game *pGame = (Game *)data;

	Game_Keyboard(pGame);

	Game_Mouse(pGame);

	Sim_Update(&pGame->sim, 0.016);
}

void Game_Draw(void *data)
{
	Game *pGame = (Game *)data;

	SimRenderer_Render(&pGame->simRenderer, &pGame->sim, &pGame->theme);

	DrawFPS(0, 0);
}

void Game_Keyboard(Game *pGame)
{
	if (IsKeyPressed(KEY_ONE))
	{
		pGame->currentId = ELEMENT_SAND;
	}
	else if (IsKeyPressed(KEY_TWO))
	{
		pGame->currentId = ELEMENT_WATER;
	}
	else if (IsKeyPressed(KEY_THREE))
	{
		pGame->currentId = ELEMENT_STONE;
	}
	else if (IsKeyPressed(KEY_FOUR))
	{
		pGame->currentId = ELEMENT_GLASS;
	}
	else if (IsKeyPressed(KEY_FIVE))
	{
		pGame->currentId = ELEMENT_LAVA;
	}
	else if (IsKeyPressed(KEY_SIX))
	{
		pGame->currentId = ELEMENT_EMPTY;
	}
	else if (IsKeyPressed(KEY_SEVEN))
	{
		pGame->currentId = ELEMENT_EMPTY;
	}
	else if (IsKeyPressed(KEY_EIGHT))
	{
		pGame->currentId = ELEMENT_EMPTY;
	}
	else if (IsKeyPressed(KEY_NINE))
	{
		pGame->currentId = ELEMENT_EMPTY;
	}
	else if (IsKeyPressed(KEY_ZERO))
	{
		pGame->currentId = ELEMENT_EMPTY;
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

	pGame->sim.current[index].id = pGame->currentId;
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
	};

	Game_Init(data);

	return scene;
}
