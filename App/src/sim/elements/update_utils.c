#include "update_utils.h"

bool isElementMoveValid(const Grid *pGrid, int current, int target)
{
	if (!Grid_IsIndexValid(pGrid, target))
		return false;

	const ElementId currentId = pGrid->current[current];
	const ElementId targetId = pGrid->current[target];

	const ElementMetadata *currentMetadata = ElementTable_Get(currentId);
	const ElementMetadata *targetMetadata = ElementTable_Get(targetId);

	const int currentDisplaceability = currentMetadata->displaceability;
	const int targetDisplaceability = targetMetadata->displaceability;

	if (targetDisplaceability <= currentDisplaceability)
		return false;

	return true;
}
