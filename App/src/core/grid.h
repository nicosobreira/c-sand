#pragma once

#include <stddef.h>

#include "core/cell.h"
#include "utils/clock.h"

typedef struct Grid
{
	Clock physicsClock;

	CellType *current;
	CellType *next;

	/// The number of cells allocated of current and next array.
	/// Equals to (width * height)
	size_t totalCells;

	int width;
	int height;
} Grid;

void Grid_Init(Grid *pGrid, int width, int height);

void Grid_Update(Grid *pGrid, double delta);

void Grid_Draw(Grid *pGrid, CellsColors *pColors, Rectangle *pView, int cellSize);

void Grid_Free(Grid *pGrid);

/* Converts a 2D grid coordinate to a 1D array
 * @return the converted index
 */
int Grid_GetIndex(int j, int i, int width);
