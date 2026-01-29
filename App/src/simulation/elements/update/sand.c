#include "sand.h"

#include "simulation/sim.h"

#include "simulation/elements/update_utils.h"

static const int g_Size = 2;

static void shuffle(int directions[g_Size])
{
	int temp = directions[0];

	directions[0] = directions[1];
	directions[1] = temp;
}

void update_Sand(Sim *pSim, int index)
{
	pSim->sandCount++;

	int target = -1;

	const int indexBellow = index + pSim->width;

	if (isElementMoveValid(pSim, indexBellow))
	{
		target = indexBellow;
	}
	else
	{
		int directions[2] = {1, -1};

		if (pSim->randomNumber100 >= 50)
			shuffle(directions);

		for (int d = 0; d < g_Size - 1; ++d)
		{
			if (!isElementMoveValid(pSim, indexBellow + directions[d]))
				continue;

			target = indexBellow + directions[d];
		}
	}

	if (target <= -1)
		return;

	Sim_UpdateIndex(pSim, index, ELEMENT_EMPTY);

	Sim_UpdateIndex(pSim, target, ELEMENT_SAND);
}
