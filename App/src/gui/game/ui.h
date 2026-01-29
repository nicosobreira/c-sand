#pragma once

#include "gui/game/elements.h"

typedef struct GameUi
{
	ElementsUi elements;
} GameUi;

static inline void GameUi_Init(GameUi *pUi)
{
	ElementsUi_Init(&pUi->elements);
}

static inline void GameUi_Draw(GameUi *pUi, Theme *pTheme)
{
	ElementsUi_Draw(&pUi->elements, pTheme);
}
