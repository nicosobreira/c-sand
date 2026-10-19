#pragma once

#include <stddef.h>

#include "simulation/elements/update_utils.h"
#include "simulation/sim.h"

static const int g_Size = 2;

static void sand_shuffle(int directions[g_Size])
{
	int temp = directions[0];

	directions[0] = directions[1];
	directions[1] = temp;
}

static void update_Sand(Sim *pSim, int index)
{
	int target = -1;

	const int indexBellow = index + pSim->width;

	if (isElementMoveValid(pSim, indexBellow))
	{
		target = indexBellow;
	}
	else
	{
		int dir = (pSim->randomNumber100 > 50) ? 1 : -1;

		for (int d = 0; d < g_Size - 1; ++d)
		{
			if (!isElementMoveValid(pSim, indexBellow + dir))
				continue;

			target = indexBellow + dir;
		}
	}

	if (target <= -1)
		return;

	Sim_UpdateIndex(pSim, index, ELEMENT_EMPTY);

	Sim_UpdateIndex(pSim, target, ELEMENT_SAND);
}
