#pragma once

#include <assert.h>
#include <stddef.h>

#include "simulation/elements/id.h"
#include "utils/clock.h"

typedef struct Sim
{
	Clock physicsClock;

	/// The number of cells allocated of current and next array.
	/// Equals to (width * height).
	size_t totalCells;

	/// Dynamic memory allocated array for reading sim data.
	/// Has totalCells as capacity.
	ElementId *current;

	/// Dynamic memory allocated array for updating sim data.
	/// Has totalCells as capacity.
	ElementId *next;

	/// Random number between 0 and 100.
	/// The value is updated on `Sim_Update`.
	int randomNumber100;

	int width;
	int height;
} Sim;

void Sim_Init(Sim *pSim, int width, int height);

void Sim_Update(Sim *pSim, double delta);

void Sim_Free(Sim *pSim);

/// Converts a 2D sim coordinate to a 1D array
static inline int Sim_GetIndex(int j, int i, int width)
{
	return j * width + i;
}

static inline bool Sim_IsIndexValid(Sim *pSim, int i)
{
	if (i >= 0 && i < pSim->totalCells)
		return true;

	return false;
}

static inline void Sim_UpdateIndex(Sim *pSim, int index, ElementId id)
{
	assert(Sim_IsIndexValid(pSim, index));

	pSim->next[index] = id;
}
