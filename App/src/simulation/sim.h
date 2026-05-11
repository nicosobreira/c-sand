#pragma once

#include <assert.h>
#include <stddef.h>

#include "simulation/elements/element.h"
#include "utils/clock.h"

typedef struct Sim
{
	Clock physicsClock;

	/// The number of cells allocated of current and next array.
	/// Equals to (width * height).
	size_t size;
	size_t sizeBytes;

	/// Dynamic memory allocated array for reading sim data.
	/// Has size as capacity.
	Element *current;

	/// Dynamic memory allocated array for updating sim data.
	/// Has size as capacity.
	Element *next;

	/// Random number between 0 and 100.
	/// The value is updated on `Sim_Update`.
	int randomNumber100;

	int width;
	int height;

	int sandCount;
} Sim;

void Sim_Init(Sim *pSim, int width, int height);

void Sim_Free(Sim *pSim);

void Sim_Update(Sim *pSim, double delta);

void Sim_UserAddElement(Sim *pSim, int index, ElementId e);

/// Converts a 2D sim coordinate to a 1D array
static inline int Sim_GetIndex(int j, int i, int width)
{
	return j * width + i;
}

static inline bool Sim_IsIndexValid(Sim *pSim, int i)
{
	if (i >= 0 && i < pSim->size)
		return true;

	return false;
}

static inline ElementId Sim_GetId(Sim *pSim, int index)
{
	assert(Sim_IsIndexValid(pSim, index));
	return pSim->current[index].id;
}

static inline void Sim_UpdateIndex(Sim *pSim, int index, ElementId id)
{
	assert(Sim_IsIndexValid(pSim, index));

	pSim->next[index].id = id;
}
