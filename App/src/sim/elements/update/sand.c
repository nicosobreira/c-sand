#include "sand.h"

#include "sim/grid.h"

#include "sim/elements/update_utils.h"

#include "raylib.h"

void update_Sand(Grid *pGrid, int index)
{
	const int min = 1;
	const int max = 99;

	/** Change of the sand to don't move diagonally.
	 * Range from 0 to 100.
	 * 0   - Always move.
	 * 100 - Stays in the same place.
	 */
	const int piling = 30;

	int target = 0;

	const int indexBellow = index + pGrid->width;

	if (isElementMoveValid(pGrid, index, indexBellow))
	{
		target = indexBellow;
	}
	else if (isElementMoveValid(pGrid, index, indexBellow + 1)) // Diagonal Right
	{
		int randomValue = GetRandomValue(min, max);
		if (randomValue < piling)
			return;

		target = indexBellow + 1;
	}
	else if (isElementMoveValid(pGrid, index, indexBellow - 1)) // Diagonal Left
	{
		int randomValue = GetRandomValue(min, max);
		if (randomValue < piling)
			return;

		target = indexBellow - 1;
	}
	else
	{
		return;
	}

	Grid_UpdateIndex(pGrid, index, ELEMENT_EMPTY);

	Grid_UpdateIndex(pGrid, target, ELEMENT_SAND);
}
