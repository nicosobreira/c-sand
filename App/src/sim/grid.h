#pragma once

#include <assert.h>
#include <stddef.h>

#include "sim/elements/id.h"
#include "utils/clock.h"

typedef struct Grid
{
	Clock physicsClock;

	/// The number of cells allocated of current and next array.
	/// Equals to (width * height).
	size_t totalCells;

	/// Dynamic memory allocated array for reading grid data.
	/// Has totalCells as capacity.
	ElementId *current;

	/// Dynamic memory allocated array for updating grid data.
	/// Has totalCells as capacity.
	ElementId *next;

	/// Random number between 0 and 100.
	/// The value is updated on `Grid_Update`.
	int randomNumber100;

	int width;
	int height;
} Grid;

void Grid_Init(Grid *pGrid, int width, int height);

void Grid_Update(Grid *pGrid, double delta);

void Grid_Free(Grid *pGrid);

/// Converts a 2D grid coordinate to a 1D array
static inline int Grid_GetIndex(int j, int i, int width)
{
	return j * width + i;
}

static inline bool Grid_IsIndexValid(Grid *pGrid, int i)
{
	if (i >= 0 && i < pGrid->totalCells)
		return true;

	return false;
}

static inline void Grid_UpdateIndex(Grid *pGrid, int index, ElementId id)
{
	assert(Grid_IsIndexValid(pGrid, index));

	pGrid->next[index] = id;
}
