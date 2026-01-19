#include "water.h"

#include "sim/grid.h"

#include "sim/elements/update_utils.h"

static inline bool isMoveValid(Grid *pGrid, int current, int target)
{
	return (isElementMoveValid(pGrid, current, target) && pGrid->next[target] == ELEMENT_EMPTY);
}

void update_Water(Grid *pGrid, int index)
{
	int target = -1;

	const int indexBellow = index + pGrid->width;

	if (isMoveValid(pGrid, index, indexBellow))
	{
		target = indexBellow;
	}
	else
	{
		int direction = pGrid->randomNumber100 > 50 ? -1 : 1;

		if (isMoveValid(pGrid, index, indexBellow - direction))
		{
			target = indexBellow - direction;
		}
		else if (isMoveValid(pGrid, index, indexBellow + direction))
		{
			target = indexBellow + direction;
		}
		else if (isMoveValid(pGrid, index, index + 1))
		{
			target = index + 1;
		}
		else if (isMoveValid(pGrid, index, index - 1))
		{
			target = index - 1;
		}
	}

	if (target == -1)
	{
		return;
	}

	Grid_UpdateIndex(pGrid, index, ELEMENT_EMPTY);
	Grid_UpdateIndex(pGrid, target, ELEMENT_WATER);
}
