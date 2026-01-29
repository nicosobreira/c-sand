#include "water.h"

#include "simulation/sim.h"

#include "simulation/elements/update_utils.h"

void update_Water(Sim *pSim, int index)
{
	int target = -1;

	const int indexBellow = index + pSim->width;

	if (isElementMoveValid(pSim, indexBellow))
	{
		target = indexBellow;
	}
	else
	{
		int direction = pSim->randomNumber100 > 50 ? -1 : 1;

		if (isElementMoveValid(pSim, indexBellow - direction))
		{
			target = indexBellow - direction;
		}
		else if (isElementMoveValid(pSim, indexBellow + direction))
		{
			target = indexBellow + direction;
		}
		else if (isElementMoveValid(pSim, index + 1))
		{
			target = index + 1;
		}
		else if (isElementMoveValid(pSim, index - 1))
		{
			target = index - 1;
		}
	}

	if (target == -1)
	{
		return;
	}

	Sim_UpdateIndex(pSim, index, ELEMENT_EMPTY);
	Sim_UpdateIndex(pSim, target, ELEMENT_WATER);
}
