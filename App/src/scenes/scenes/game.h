#pragma once

#include "render/sim/renderer.h"
#include "simulation/sim.h"
#include "ui/game/ui.h"
#include "ui/theme.h"

#include "scenes/scene.h"

typedef struct Game
{
	SimRenderer simRenderer;
	Sim sim;
	Theme theme;
	GameUi ui;
} Game;

void Game_Init(void *data);

void Game_Free(void *data);

void Game_Update(void *data);

void Game_Draw(void *data);

void Game_Keyboard(Game *pGame);

void Game_Mouse(Game *pGame);

static inline void Game_Resize(Game *pGame)
{
	SimRenderer_Resize(&pGame->simRenderer, &pGame->sim);
}

Scene Game_Scene(void);
