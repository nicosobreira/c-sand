#include "sim.h"

#include <stdlib.h>
#include <string.h>

#include "simulation/elements/table.h"
#include "utils/free.h"

static inline void swapBuffers(Element **current, Element **next)
{
	Element *temp = *current;

	*current = *next;
	*next = temp;
}

static void handleError(const char *msg)
{
	TraceLog(LOG_ERROR, "%s", msg);
	CloseWindow();
	exit(EXIT_FAILURE);
}

void Sim_Init(Sim *pSim, int width, int height)
{
	pSim->width = width;
	pSim->height = height;

	pSim->size = (size_t)(pSim->width * pSim->height);
	pSim->sizeBytes = (size_t)(sizeof(Element) * pSim->size);

	pSim->current = malloc(pSim->sizeBytes);
	pSim->next = malloc(pSim->sizeBytes);

	memset(pSim->current, ELEMENT_EMPTY, pSim->sizeBytes);
	memset(pSim->next, ELEMENT_EMPTY, pSim->sizeBytes);

	if (pSim->current == NULL || pSim->next == NULL)
	{
		handleError("Out of Memory");
	}

	const double newTime = 0.04;

	Clock_Set(&pSim->physicsClock, newTime);

	// Default value
	// /*
	for (size_t i = 0; i < pSim->size; ++i)
	{
		int random = GetRandomValue(0, 9);
		switch (random)
		{
		case 0:
			pSim->current[i].id = ELEMENT_STONE;
			break;
		case 1:
			pSim->current[i].id = ELEMENT_SAND;
		}
	}
	// */
}

void Sim_Free(Sim *pSim)
{
	FREE(pSim->current);
	FREE(pSim->next);
}

void Sim_Update(Sim *pSim, double delta)
{
	if (!Clock_Tick(&pSim->physicsClock, delta))
		return;

	pSim->randomNumber100 = GetRandomValue(0, 100);

	// Copy current state into next
	memcpy(pSim->next, pSim->current, pSim->sizeBytes);

	// TODO: This is the major drawback in my code.
	// Use a Data Oriented Design instead
	ElementTable_Update(pSim);

	swapBuffers(&pSim->next, &pSim->current);
}

void Sim_UserAddElement(Sim *pSim, int index, ElementId e)
{
	ElementId targetId = e;
	int direction = pSim->randomNumber100 <= 50 ? -1 : 1;

	while (targetId != ELEMENT_EMPTY)
	{
		index += pSim->width + direction;
		targetId = Sim_GetId(pSim, index);
	}

	pSim->current[index].id = e;
}
