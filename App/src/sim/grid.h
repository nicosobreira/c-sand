#pragma once

#include <assert.h>
#include <stddef.h>

#include "sim/elements/id.h"
#include "utils/clock.h"

typedef struct Grid
{
	Clock physicsClock;

	/// The number of cells allocated of current and next array.
	/// Equals to (width * height)
	size_t totalCells;

	/// Dynamic memory allocated array for reading grid data
	/// Has totalCells as capacity;
	ElementId *current;

	/// Dynamic memory allocated array for updating grid data
	/// Has totalCells as capacity;
	ElementId *next;

	/// Dynamic memory allocated array holding only the indexes update
	/// Has totalCells as capacity;
	int *updatedIndexes;
	int updatedCurrentSize;

	int width;
	int height;
} Grid;

void Grid_Init(Grid *pGrid, int width, int height);

void Grid_Update(Grid *pGrid, double delta);

void Grid_Free(Grid *pGrid);

static inline void Grid_UpdatedIndexesAdd(Grid *pGrid, int index)
{
	assert(pGrid->updatedCurrentSize + 1 < pGrid->totalCells);

	pGrid->updatedCurrentSize++;
	pGrid->updatedIndexes[pGrid->updatedCurrentSize] = index;
}

/// Converts a 2D grid coordinate to a 1D array
static inline int Grid_GetIndex(int j, int i, int width)
{
	return j * width + i;
}

static inline bool Grid_IsIndexValid(const Grid *pGrid, int i)
{
	if (i >= 0 && i < pGrid->totalCells)
		return true;

	return false;
}
