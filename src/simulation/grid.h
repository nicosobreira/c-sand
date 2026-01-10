#pragma once

#include "simulation/cell.h"
#include "utils/clock.h"

typedef struct Grid
{
	Clock updateClock;
	/// Stores the grid of cells in array
	CellType *buffer;
	int width;
	int height;
	int cellSize;
} Grid;

void Grid_Init(Grid *pGrid, int width, int height, int cellSize);

void Grid_Render(Grid *pGrid);

void Grid_Update(Grid *pGrid, double delta);

void Grid_Free(Grid *pGrid);
