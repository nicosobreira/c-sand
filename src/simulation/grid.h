#pragma once

#include <stddef.h>

#include "simulation/cell.h"
#include "utils/clock.h"

typedef struct Grid
{
	Clock physicsClock;

	CellType *current;
	CellType *next;

	/// The number of cells allocated of current and next array
	size_t totalCells;

	int width;
	int height;
	int cellSize;
} Grid;

void Grid_Init(Grid *pGrid, int width, int height, int cellSize);

void Grid_Render(Grid *pGrid);

void Grid_Update(Grid *pGrid, double delta);

void Grid_Free(Grid *pGrid);

/* Converts a 2D grid coordinate to a 1D array
 * @return the converted index
 */
int Grid_GetIndex(int j, int i, int width);
