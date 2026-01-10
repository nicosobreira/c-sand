#include "grid.h"

#include <stdlib.h>
#include <string.h>

#include "raylib.h"

/* Converts a 2D grid coordinate to a 1D array
 * @return the converted index
 */
static int getGridIndex(int j, int i, int width)
{
	return j * width + i;
}

void Grid_Init(Grid *pGrid, int width, int height, int cellSize)
{
	memset(pGrid, 0, sizeof(Grid));

	Clock_Set(&pGrid->updateClock, cellSize / (double)width);

	// TODO: This shouldn't be hard coded
	pGrid->width = width;
	pGrid->height = height;
	pGrid->cellSize = cellSize;

	const size_t totalCells = (size_t)(pGrid->width * pGrid->height);

	pGrid->buffer = MemAlloc((unsigned int)(sizeof(CellType) * totalCells));

	if (pGrid->buffer == NULL)
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
			int index = getGridIndex(j, i, pGrid->width);

			int random = GetRandomValue(0, 9);
			if (random == 0)
			{
				pGrid->buffer[index] = CELL_SAND;
				continue;
			}

			pGrid->buffer[index] = CELL_EMPTY;
		}
	}
}

void Grid_Update(Grid *pGrid, double delta)
{
	if (!Clock_Tick(&pGrid->updateClock, delta))
		return;

	// Because the sand is falling the loop has to be from the bottom
	for (int j = pGrid->height - 1; j >= 0; j--)
	{
		for (int i = pGrid->width - 1; i >= 0; i--)
		{
			int index = getGridIndex(j, i, pGrid->width);

			if (pGrid->buffer[index] == CELL_EMPTY)
				continue;

			/// Remember: It is zero indexed
			const int maxIndex = pGrid->width * pGrid->height - 1;

			// Sand cannot fall
			int indexBellow = index + pGrid->width;

			if (indexBellow > maxIndex)
				continue;

			if (pGrid->buffer[indexBellow] != CELL_EMPTY)
				continue;

			pGrid->buffer[index] = CELL_EMPTY;
			pGrid->buffer[indexBellow] = CELL_SAND;
		}
	}
}

void Grid_Render(Grid *pGrid)
{
	const int offset = 20;

	// clang-format off
	DrawRectangle(
		offset,
		offset,
		(pGrid->width - 1) * pGrid->cellSize + offset,
		(pGrid->height - 1) * pGrid->cellSize + offset,
		BLACK
	);
	// clang-format on

	for (int i = 0; i < pGrid->width; ++i)
	{
		for (int j = 0; j < pGrid->height; ++j)
		{
			int index = getGridIndex(j, i, pGrid->width);

			int x = i * pGrid->cellSize + offset;
			int y = j * pGrid->cellSize + offset;

			switch (pGrid->buffer[index])
			{
			case CELL_EMPTY:
				break;
			case CELL_SAND:
				DrawRectangle(x, y, pGrid->cellSize, pGrid->cellSize, YELLOW);
				break;
			}
		}
	}
}

void Grid_Free(Grid *pGrid)
{
	MemFree(pGrid->buffer);

	memset(pGrid, 0, sizeof(Grid));
}
