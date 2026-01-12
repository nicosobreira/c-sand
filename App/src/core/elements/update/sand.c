#include "sand.h"

#include <stddef.h>

#include "core/grid.h"

/** Check if the index bellow is valid
 * @param current valid pGrid cell index
 * @param target unkown cell index
 */
static inline bool isCellMoveValid(const Grid *pGrid, size_t current, size_t target)
{
	if (target >= pGrid->totalCells)
		return false;
	return true;
}

void update_Sand(const Grid *pGrid, size_t index)
{
	/// Remember: It is zero indexed
	const int maxIndex = (int)pGrid->totalCells - 1;

	// Sand cannot fall
	const int indexBellow = index + pGrid->width;

	if (indexBellow > maxIndex)
		return;

	const int indexDiagonalRight = indexBellow + pGrid->height;

	if (pGrid->current[indexBellow] != ELEMENT_EMPTY)
	{
		return;
	}

	pGrid->next[index] = ELEMENT_EMPTY;
	pGrid->next[indexBellow] = ELEMENT_SAND;
}
