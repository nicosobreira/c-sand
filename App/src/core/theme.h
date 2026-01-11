#pragma once

#include "core/cell.h"

typedef struct Theme
{
	CellsColors cells;
	Color backgrond;
} Theme;

typedef enum ThemeId
{
	THEME_CATPPUCCIN_MOCHA
} ThemeId;

void Theme_Init(Theme *pTheme, ThemeId id);
