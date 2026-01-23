#include "sand.h"

#include "simulation/sim.h"

#include "simulation/elements/update_utils.h"

void update_Sand(Sim *pSim, int index)
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

	const int indexBellow = index + pSim->width;

	if (isElementMoveValid(pSim, index, indexBellow))
	{
		target = indexBellow;
	}
	else if (isElementMoveValid(pSim, index, indexBellow + 1)) // Diagonal Right
	{
		if (pSim->randomNumber100 < piling)
			return;

		target = indexBellow + 1;
	}
	else if (isElementMoveValid(pSim, index, indexBellow - 1)) // Diagonal Left
	{
		if (pSim->randomNumber100 < piling)
			return;

		target = indexBellow - 1;
	}
	else
	{
		return;
	}

	Sim_UpdateIndex(pSim, index, ELEMENT_EMPTY);

	Sim_UpdateIndex(pSim, target, ELEMENT_SAND);
}
