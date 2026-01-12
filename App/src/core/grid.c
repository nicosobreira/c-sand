#include "grid.h"

#include <stdlib.h>
#include <string.h>

#include "core/elements/cache.h"

static void swapBuffers(ElementId **current, ElementId **next)
{
	ElementId *temp = *current;

	*current = *next;
	*next = temp;
}

static void handleElementTotal(void)
{
	TraceLog(LOG_ERROR, "Out of memory!");
	CloseWindow();
	exit(EXIT_FAILURE);
}

void Grid_Init(Grid *pGrid, int width, int height)
{
	memset(pGrid, 0, sizeof(Grid));

	pGrid->width = width;
	pGrid->height = height;

	pGrid->totalCells = (size_t)(pGrid->width * pGrid->height);

	pGrid->current = MemAlloc((unsigned int)(sizeof(ElementId) * pGrid->totalCells));
	pGrid->next = MemAlloc((unsigned int)(sizeof(ElementId) * pGrid->totalCells));

	memset(pGrid->current, ELEMENT_EMPTY, sizeof(ElementId) * pGrid->totalCells);
	memset(pGrid->next, ELEMENT_EMPTY, sizeof(ElementId) * pGrid->totalCells);

	if (pGrid->current == NULL || pGrid->next == NULL)
	{
		handleElementTotal();
	}

	const double newTime = 0.04;

	Clock_Set(&pGrid->physicsClock, newTime);

	SetRandomSeed((unsigned int)GetTime() * 1000);

	for (int i = 0; i < pGrid->totalCells; ++i)
	{
		int random = GetRandomValue(0, 9);
		if (random == 0)
		{
			pGrid->current[i] = ELEMENT_SAND;
		}
	}
}

void Grid_Update(Grid *pGrid, double delta)
{
	if (!Clock_Tick(&pGrid->physicsClock, delta))
		return;

	// Copy current state into next
	memcpy(pGrid->next, pGrid->current, sizeof(ElementId) * pGrid->totalCells);

	for (int i = 0; i < pGrid->totalCells; ++i)
	{
		if (pGrid->current[i] == ELEMENT_EMPTY)
			continue;

		g_ElementUpdate[pGrid->current[i]](pGrid, i);
	}

	swapBuffers(&pGrid->current, &pGrid->next);
}

void Grid_Draw(Grid *pGrid, Theme *pTheme, Rectangle *pView, int cellSize, GridRenderCache *pCache)
{
	Color elementColors[ELEMENT_TOTAL];
	for (int e = 0; e < ELEMENT_TOTAL; ++e)
		elementColors[e] = pTheme->elements[e].color;

	DrawRectangleRec(*pView, elementColors[ELEMENT_EMPTY]);

	for (int j = 0; j < pGrid->height; ++j)
	{
		int row = j * pGrid->width;

		for (int i = 0; i < pGrid->width; ++i)
		{
			ElementId e = pGrid->current[row + i];
			/*
			if (e == ELEMENT_EMPTY)
			    continue;
		   */

			pCache->pixels[row + i] = elementColors[e];
		}
	}
	UpdateTexture(pCache->texture, pCache->pixels);

	// 4️⃣ Draw texture ONCE (scaled)
	DrawTextureEx(pCache->texture, (Vector2){pView->x, pView->y}, 0.0f, (float)cellSize, WHITE);
}

void Grid_Free(Grid *pGrid)
{
	MemFree(pGrid->current);
	MemFree(pGrid->next);

	memset(pGrid, 0, sizeof(Grid));
}
