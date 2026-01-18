#include "water.h"

#include "sim/grid.h"

#include "sim/elements/update_utils.h"

// FIX: Water only form pools on the right

static bool isPressurized(Grid *pGrid, int index)
{
	const int aboveIndex = index - pGrid->width;

	if (!Grid_IsIndexValid(pGrid, index))
		return false;

	const ElementId aboveId = pGrid->current[aboveIndex];

	if (aboveId == ELEMENT_EMPTY)
		return false;

	return true;
}

void update_Water(Grid *pGrid, int index)
{
	int target = 0;

	const int indexBellow = index + pGrid->width;

	if (isElementMoveValid(pGrid, index, indexBellow))
	{
		target = indexBellow;
	}
	else if (isElementMoveValid(pGrid, index, indexBellow + 1)) // Diagonal Right
	{
		target = indexBellow + 1;
	}
	else if (isElementMoveValid(pGrid, index, indexBellow - 1)) // Diagonal Left
	{
		target = indexBellow - 1;
	}
	else if (isElementMoveValid(pGrid, index, index + 1)) // Right
	{
		target = index + 1;
	}
	else
	{
		return;
	}

	Grid_UpdateIndex(pGrid, index, ELEMENT_EMPTY);

	Grid_UpdateIndex(pGrid, target, ELEMENT_WATER);
}
