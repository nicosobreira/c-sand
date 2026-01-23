#include "sim.h"

#include <stdlib.h>
#include <string.h>

#include "simulation/elements/table.h"

static inline void swapBuffers(ElementId **current, ElementId **next)
{
	ElementId *temp = *current;

	*current = *next;
	*next = temp;
}

static void handleError(void)
{
	TraceLog(LOG_ERROR, "Out of memory!");
	CloseWindow();
	exit(EXIT_FAILURE);
}

void Sim_Init(Sim *pSim, int width, int height)
{
	memset(pSim, 0, sizeof(Sim));

	pSim->width = width;
	pSim->height = height;

	pSim->totalCells = (size_t)(pSim->width * pSim->height);

	pSim->current = malloc((size_t)(sizeof(ElementId) * pSim->totalCells));
	pSim->next = malloc((size_t)(sizeof(ElementId) * pSim->totalCells));

	memset(pSim->current, ELEMENT_EMPTY, sizeof(ElementId) * pSim->totalCells);
	memset(pSim->next, ELEMENT_EMPTY, sizeof(ElementId) * pSim->totalCells);

	if (pSim->current == NULL || pSim->next == NULL)
	{
		handleError();
	}

	const double newTime = 0.04;

	Clock_Set(&pSim->physicsClock, newTime);

	// Default value
	/*
	for (size_t i = 0; i < pSim->totalCells; ++i)
	{
	    int random = GetRandomValue(0, 9);
	    switch (random)
	    {
	    case 0:
	        pSim->current[i] = ELEMENT_SAND;
	        break;
	    case 1:
	        pSim->current[i] = ELEMENT_STONE;
	    }
	}
	*/
}

void Sim_Update(Sim *pSim, double delta)
{
	if (!Clock_Tick(&pSim->physicsClock, delta))
		return;

	pSim->randomNumber100 = GetRandomValue(0, 100);

	// Copy current state into next
	memcpy(pSim->next, pSim->current, sizeof(ElementId) * pSim->totalCells);

	for (int i = pSim->totalCells - 1; i >= 0; --i)
	{
		ElementTable_Update(pSim, i);
	}

	swapBuffers(&pSim->current, &pSim->next);
}

void Sim_Free(Sim *pSim)
{
	free(pSim->current);
	free(pSim->next);

	memset(pSim, 0, sizeof(Sim));
}
