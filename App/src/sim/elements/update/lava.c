#include "lava.h"

#include <stddef.h>

#include "sim/grid.h"

#include "sim/elements/update_utils.h"

static void ignate(Grid *pGrid, int target)
{
	const ElementId targetId = pGrid->current[target];

	if (targetId == ELEMENT_SAND)
	{
		Grid_UpdateIndex(pGrid, target, ELEMENT_GLASS);
	}
}

void update_Lava(Grid *pGrid, int index)
{
	if (Grid_IsIndexValid(pGrid, index - pGrid->width)) // Up
	{
		ignate(pGrid, index - pGrid->width);
	}
	if (Grid_IsIndexValid(pGrid, index + pGrid->width)) // Down
	{
		ignate(pGrid, index + pGrid->width);
	}
	if (Grid_IsIndexValid(pGrid, index - 1)) // Left
	{
		ignate(pGrid, index - 1);
	}
	if (Grid_IsIndexValid(pGrid, index + 1)) // Right
	{
		ignate(pGrid, index + 1);
	}

	// Movement
	int target = 0;
	const int indexBellow = index + pGrid->width;

	if (isElementMoveValid(pGrid, index, indexBellow))
	{
		target = indexBellow;
	}
	else
	{
		return;
	}

	Grid_UpdateIndex(pGrid, index, ELEMENT_EMPTY);
	Grid_UpdateIndex(pGrid, target, ELEMENT_LAVA);
}
