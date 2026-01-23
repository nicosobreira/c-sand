#include "update_utils.h"

#include "table.h"

bool isElementMoveValid(Sim *pSim, int current, int target)
{
	if (!Sim_IsIndexValid(pSim, target))
		return false;

	const ElementId currentId = pSim->current[current];
	const ElementId targetId = pSim->current[target];

	const ElementMetadata *currentMetadata = ElementTable_Get(currentId);
	const ElementMetadata *targetMetadata = ElementTable_Get(targetId);

	const int currentDisplaceability = currentMetadata->displaceability;
	const int targetDisplaceability = targetMetadata->displaceability;

	if (targetDisplaceability <= currentDisplaceability)
		return false;

	return true;
}
