#include "grid.h"

#include <stdlib.h>
#include <string.h>

#include "sim/elements/table.h"

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

void Grid_Init(Grid *pGrid, int width, int height)
{
	memset(pGrid, 0, sizeof(Grid));

	pGrid->width = width;
	pGrid->height = height;

	pGrid->totalCells = (size_t)(pGrid->width * pGrid->height);

	pGrid->current = malloc((size_t)(sizeof(ElementId) * pGrid->totalCells));
	pGrid->next = malloc((size_t)(sizeof(ElementId) * pGrid->totalCells));

	memset(pGrid->current, ELEMENT_EMPTY, sizeof(ElementId) * pGrid->totalCells);
	memset(pGrid->next, ELEMENT_EMPTY, sizeof(ElementId) * pGrid->totalCells);

	if (pGrid->current == NULL || pGrid->next == NULL)
	{
		handleError();
	}

	const double newTime = 0.04;

	Clock_Set(&pGrid->physicsClock, newTime);

	// Default value
	/*
	for (size_t i = 0; i < pGrid->totalCells; ++i)
	{
	    int random = GetRandomValue(0, 9);
	    switch (random)
	    {
	    case 0:
	        pGrid->current[i] = ELEMENT_SAND;
	        break;
	    case 1:
	        pGrid->current[i] = ELEMENT_STONE;
	    }
	}
	*/
}

void Grid_Update(Grid *pGrid, double delta)
{
	if (!Clock_Tick(&pGrid->physicsClock, delta))
		return;

	pGrid->randomNumber100 = GetRandomValue(0, 100);

	// Copy current state into next
	memcpy(pGrid->next, pGrid->current, sizeof(ElementId) * pGrid->totalCells);

	for (int i = pGrid->totalCells - 1; i >= 0; --i)
	{
		ElementTable_Update(pGrid, i);
	}

	swapBuffers(&pGrid->current, &pGrid->next);
}

void Grid_Free(Grid *pGrid)
{
	free(pGrid->current);
	free(pGrid->next);

	memset(pGrid, 0, sizeof(Grid));
}
