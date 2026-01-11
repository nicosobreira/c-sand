#include "grid.h"

#include <stdlib.h>
#include <string.h>

static void swapBuffers(CellType **current, CellType **next)
{
	CellType *temp = *current;

	*current = *next;
	*next = temp;
}

void Grid_Init(Grid *pGrid, int width, int height)
{
	memset(pGrid, 0, sizeof(Grid));

	// TODO: This shouldn't be hard coded
	pGrid->width = width;
	pGrid->height = height;

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

	const double newTime = 0.04;

	Clock_Set(&pGrid->physicsClock, newTime);

	SetRandomSeed((unsigned int)GetTime() * 1000);

	for (int i = 0; i < pGrid->width; ++i)
	{
		for (int j = 0; j < pGrid->height; ++j)
		{
			int index = Grid_GetIndex(j, i, pGrid->width);

			int random = GetRandomValue(0, 9);
			if (random == 0)
			{
				pGrid->current[index] = CELL_SAND;
			}
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
	for (int j = 0; j < pGrid->height; ++j)
	{
		for (int i = 0; i < pGrid->width; ++i)
		{
			int index = Grid_GetIndex(j, i, pGrid->width);

			if (pGrid->current[index] == CELL_EMPTY)
			{
				continue;
			}

			/// Remember: It is zero indexed
			int maxIndex = (int)pGrid->totalCells - 1;

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

void Grid_Draw(Grid *pGrid, CellsColors *pColors, Rectangle *pView, int cellSize)
{
	DrawRectangleRec(*pView, pColors->empty);

	int xPositions[pGrid->width];
	int yPositions[pGrid->height];

	for (int i = 0; i < pGrid->width; i++)
		xPositions[i] = i * cellSize + (int)pView->x;

	for (int j = 0; j < pGrid->height; j++)
		yPositions[j] = j * cellSize + (int)pView->y;

	for (int i = 0; i < pGrid->width; ++i)
	{
		for (int j = 0; j < pGrid->height; ++j)
		{
			int index = Grid_GetIndex(j, i, pGrid->width);

			if (pGrid->current[index] == CELL_SAND)
			{
				DrawRectangle(xPositions[i], yPositions[j], cellSize, cellSize, pColors->sand);
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

int Grid_GetIndex(int j, int i, int width)
{
	return j * width + i;
}
