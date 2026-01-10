#include "grid.h"

#include <stdlib.h>
#include <string.h>

#include "raylib.h"

int Grid_GetIndex(int j, int i, int width)
{
	return j * width + i;
}

static void swapBuffers(CellType **current, CellType **next)
{
	CellType *temp = *current;

	*current = *next;
	*next = temp;
}

void Grid_Init(Grid *pGrid, int width, int height, int cellSize)
{
	memset(pGrid, 0, sizeof(Grid));

	Clock_Set(&pGrid->physicsClock, cellSize / (double)width);

	// TODO: This shouldn't be hard coded
	pGrid->width = width;
	pGrid->height = height;
	pGrid->cellSize = cellSize;

	pGrid->totalCells = (size_t)(pGrid->width * pGrid->height);

	pGrid->current = MemAlloc((unsigned int)(sizeof(CellType) * pGrid->totalCells));
	pGrid->next = MemAlloc((unsigned int)(sizeof(CellType) * pGrid->totalCells));

	memset(pGrid->current, CELL_EMPTY, sizeof(CellType) * pGrid->totalCells);
	memset(pGrid->next, CELL_EMPTY, sizeof(CellType) * pGrid->totalCells);

	if (pGrid->current == NULL || pGrid->next == NULL)
	{
		TraceLog(LOG_ERROR, "Out of memory!");
		CloseWindow();
		exit(EXIT_FAILURE);
	}

	SetRandomSeed(10);

	for (int i = 0; i < pGrid->width; ++i)
	{
		for (int j = 0; j < pGrid->height; ++j)
		{
			int index = Grid_GetIndex(j, i, pGrid->width);

			int random = GetRandomValue(0, 9);
			if (random == 0)
			{
				pGrid->current[index] = CELL_SAND;
				continue;
			}

			pGrid->current[index] = CELL_EMPTY;
		}
	}
}

void Grid_Update(Grid *pGrid, double delta)
{
	if (!Clock_Tick(&pGrid->physicsClock, delta))
		return;

	// Copy current state into next
	memcpy(pGrid->next, pGrid->current, sizeof(CellType) * pGrid->totalCells);

	// Because the sand is falling the loop has to start from the bottom
	for (int j = pGrid->height - 1; j >= 0; j--)
	{
		for (int i = pGrid->width - 1; i >= 0; i--)
		{
			int index = Grid_GetIndex(j, i, pGrid->width);

			if (pGrid->current[index] == CELL_EMPTY)
			{
				continue;
			}

			/// Remember: It is zero indexed
			const int maxIndex = pGrid->width * pGrid->height - 1;

			// Sand cannot fall
			int indexBellow = index + pGrid->width;

			if (indexBellow > maxIndex)
			{
				continue;
			}

			if (pGrid->current[indexBellow] != CELL_EMPTY)
			{
				continue;
			}

			pGrid->next[index] = CELL_EMPTY;
			pGrid->next[indexBellow] = CELL_SAND;
		}
	}

	swapBuffers(&pGrid->current, &pGrid->next);
}

void Grid_Render(Grid *pGrid)
{
	const int offset = 20;

	const Color ColorBackground = {
	    .a = 255,
	    .r = 30,
	    .g = 30,
	    .b = 46,
	};

	const Color ColorSand = {
	    .a = 255,
	    .r = 249,
	    .g = 226,
	    .b = 175,
	};

	// clang-format off
	DrawRectangle(
		offset,
		offset,
		(pGrid->width - 1) * pGrid->cellSize + offset,
		(pGrid->height - 1) * pGrid->cellSize + offset,
		ColorBackground
	);
	// clang-format on

	int xPositions[pGrid->width];
	int yPositions[pGrid->height];

	for (int i = 0; i < pGrid->width; i++)
		xPositions[i] = i * pGrid->cellSize + offset;

	for (int j = 0; j < pGrid->height; j++)
		yPositions[j] = j * pGrid->cellSize + offset;

	for (int i = 0; i < pGrid->width; ++i)
	{
		for (int j = 0; j < pGrid->height; ++j)
		{
			int index = Grid_GetIndex(j, i, pGrid->width);

			if (pGrid->current[index] == CELL_SAND)
			{
				DrawRectangle(xPositions[i], yPositions[j], pGrid->cellSize, pGrid->cellSize, ColorSand);
			}
		}
	}
}

void Grid_Free(Grid *pGrid)
{
	MemFree(pGrid->current);
	MemFree(pGrid->next);

	memset(pGrid, 0, sizeof(Grid));
}
