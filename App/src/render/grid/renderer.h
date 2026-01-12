#pragma once

#include "sim/grid.h"
#include "ui/theme.h"

#include "cache.h"

typedef struct GridRenderer
{
	GridRenderCache cache;
	Rectangle viewPort;
	int cellSize;
} GridRenderer;

void GridRenderer_Init(GridRenderer *pRender, Grid *pGrid);

static inline void GridRenderer_Free(GridRenderer *pRender)
{
	GridRenderCache_Free(&pRender->cache);
}

void GridRenderer_Render(GridRenderer *pRender, Grid *pGrid, Theme *pTheme);

void GridRenderer_Resize(GridRenderer *pRender, Grid *pGrid);
