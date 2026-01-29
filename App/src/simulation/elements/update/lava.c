#include "lava.h"

#include <stddef.h>

#include "simulation/sim.h"

#include "simulation/elements/update_utils.h"

static void ignate(Sim *pSim, int target)
{
	const ElementId targetId = Sim_GetId(pSim, target);

	if (targetId == ELEMENT_SAND)
	{
		Sim_UpdateIndex(pSim, target, ELEMENT_GLASS);
	}
}

void update_Lava(Sim *pSim, int index)
{
	if (Sim_IsIndexValid(pSim, index - pSim->width)) // Up
	{
		ignate(pSim, index - pSim->width);
	}
	if (Sim_IsIndexValid(pSim, index + pSim->width)) // Down
	{
		ignate(pSim, index + pSim->width);
	}
	if (Sim_IsIndexValid(pSim, index - 1)) // Left
	{
		ignate(pSim, index - 1);
	}
	if (Sim_IsIndexValid(pSim, index + 1)) // Right
	{
		ignate(pSim, index + 1);
	}

	// Movement
	int target = 0;
	const int indexBellow = index + pSim->width;

	if (isElementMoveValid(pSim, indexBellow))
	{
		target = indexBellow;
	}
	else
	{
		return;
	}

	Sim_UpdateIndex(pSim, index, ELEMENT_EMPTY);
	Sim_UpdateIndex(pSim, target, ELEMENT_LAVA);
}
