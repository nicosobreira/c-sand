#include "renderer.h"

void GridRenderer_Init(GridRenderer *pRender, Grid *pGrid)
{
	GridRenderCache_Init(&pRender->cache, pGrid->width, pGrid->height);

	GridRenderer_Resize(pRender, pGrid);
}

void GridRenderer_Render(GridRenderer *pRender, Grid *pGrid, Theme *pTheme)
{
	GridRenderCache *pCache = &pRender->cache;
	Rectangle *pView = &pRender->viewPort;
	int cellSize = pRender->cellSize;

	Color elementColors[ELEMENT_TOTAL];
	for (int e = 0; e < ELEMENT_TOTAL; ++e)
		elementColors[e] = pTheme->elements[e].color;

	DrawRectangleRec(pRender->viewPort, elementColors[ELEMENT_EMPTY]);

	for (int j = 0; j < pGrid->height; ++j)
	{
		int row = j * pGrid->width;

		for (int i = 0; i < pGrid->width; ++i)
		{
			ElementId e = pGrid->current[row + i];

			pCache->pixels[row + i] = elementColors[e];
		}
	}
	UpdateTexture(pCache->texture, pCache->pixels);

	// Draw texture ONCE (scaled)
	DrawTextureEx(pCache->texture, (Vector2){pView->x, pView->y}, 0.0f, (float)cellSize, WHITE);
}

void GridRenderer_Resize(GridRenderer *pRender, Grid *pGrid)
{
	Rectangle *pView = &pRender->viewPort;

	const float screenWidth = (float)GetScreenWidth();
	const float screenHeight = (float)GetScreenHeight();

	float cellSize = 0;

	if (screenWidth < screenHeight)
	{
		cellSize = screenWidth / (float)pGrid->width;
		pView->width = pRender->cellSize * (float)pGrid->width;
		pView->height = pRender->cellSize * (float)pGrid->height;
	}
	else
	{
		cellSize = screenHeight / (float)pGrid->height;
		pView->width = cellSize * (float)pGrid->width;
		pView->height = cellSize * (float)pGrid->height;
	}

	// BUG: Why is this equal to zero?
	pRender->cellSize = cellSize;

	pView->x = (screenWidth - pView->width) / 2.0f;
	pView->y = (screenHeight - pView->height) / 2.0f;
}
