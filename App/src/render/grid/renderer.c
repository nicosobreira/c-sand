#include "renderer.h"

#include <math.h>

void GridRenderer_Init(GridRenderer *pRender, Grid *pGrid)
{
	GridRenderCache_Init(&pRender->cache, pGrid->width, pGrid->height);

	GridRenderer_Resize(pRender, pGrid);
}

void GridRenderer_Render(GridRenderer *pRender, Grid *pGrid, const Theme *pTheme)
{
	GridRenderCache *pCache = &pRender->cache;
	Rectangle *pView = &pRender->viewPort;
	float cellSize = pRender->cellSize;

	for (size_t i = 0; i < pCache->totalPixels; ++i)
	{
		ElementId e = pGrid->current[i];
		pCache->pixels[i] = pTheme->elements[e].color;
	}

	UpdateTexture(pCache->texture, pCache->pixels);

	// Draw texture ONCE (scaled)
	DrawTextureEx(pCache->texture, (Vector2){pView->x, pView->y}, 0.0f, (float)cellSize, WHITE);
}

/** Assert that a number is even
 */
static float evenFloat(float a)
{
	return roundf(a * 0.5f) * 2.0f;
}

void GridRenderer_Resize(GridRenderer *pRender, Grid *pGrid)
{
	Rectangle *pView = &pRender->viewPort;

	const float screenWidth = (float)GetScreenWidth();
	const float screenHeight = (float)GetScreenHeight();

	float cellSize = 0;

	if (screenWidth < screenHeight)
	{
		cellSize = evenFloat(screenWidth / (float)pGrid->width);
		pView->width = pRender->cellSize * (float)pGrid->width;
		pView->height = pRender->cellSize * (float)pGrid->height;
	}
	else
	{
		cellSize = evenFloat(screenHeight / (float)pGrid->height);
		pView->width = cellSize * (float)pGrid->width;
		pView->height = cellSize * (float)pGrid->height;
	}

	pRender->cellSize = cellSize;

	pView->x = (screenWidth - pView->width) / 2.0f;
	pView->y = (screenHeight - pView->height) / 2.0f;

	TraceLog(LOG_DEBUG, "%f", cellSize);
}
