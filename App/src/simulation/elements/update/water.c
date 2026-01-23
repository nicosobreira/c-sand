#include "water.h"

#include "simulation/sim.h"

#include "simulation/elements/update_utils.h"

static inline bool isMoveValid(Sim *pSim, int current, int target)
{
	return (isElementMoveValid(pSim, current, target) && pSim->next[target].id == ELEMENT_EMPTY);
}

/*
void update_Water(Sim *pSim, int index)
{
    int target = -1;

    const int indexBellow = index + pSim->width;

    if (isMoveValid(pSim, index, indexBellow))
    {
        target = indexBellow;
    }
    else
    {
        int direction = pSim->randomNumber100 > 50 ? -1 : 1;

        if (isMoveValid(pSim, index, indexBellow - direction))
        {
            target = indexBellow - direction;
        }
        else if (isMoveValid(pSim, index, indexBellow + direction))
        {
            target = indexBellow + direction;
        }
        else if (isMoveValid(pSim, index, index + 1))
        {
            target = index + 1;
        }
        else if (isMoveValid(pSim, index, index - 1))
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
*/

static bool hasWater(Sim *pSim, int target)
{
	if (!Sim_IsIndexValid(pSim, target))
		return false;

	return pSim->next[target].id == ELEMENT_WATER;
}

void update_Water(Sim *pSim, int index)
{
	int target = -1;

	const int indexBellow = index + pSim->width;

	if (isMoveValid(pSim, index, indexBellow))
	{
		target = indexBellow;
	}
	else
	{
		int direction = pSim->randomNumber100 > 50 ? -1 : 1;

		if (isMoveValid(pSim, index, indexBellow - direction))
		{
			target = indexBellow - direction;
		}
		else if (isMoveValid(pSim, index, indexBellow + direction))
		{
			target = indexBellow + direction;
		}
		else if (isMoveValid(pSim, index, index + 1))
		{
			target = index + 1;
		}
		else if (isMoveValid(pSim, index, index - 1))
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
