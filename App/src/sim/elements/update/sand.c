#include "sand.h"

#include <stddef.h>

#include "sim/grid.h"

#include "sim/elements/update_utils.h"

void update_Sand(Grid *pGrid, int index)
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
	else
	{
		return;
	}

	pGrid->next[index] = ELEMENT_EMPTY;
	Grid_UpdatedIndexesAdd(pGrid, index);

	pGrid->next[target] = ELEMENT_SAND;
	Grid_UpdatedIndexesAdd(pGrid, target);
}
