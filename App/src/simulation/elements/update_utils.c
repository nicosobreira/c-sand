#include "update_utils.h"

#include "table.h"

bool isElementMoveValid(Sim *pSim, int current, int target)
{
	if (!Sim_IsIndexValid(pSim, target))
		return false;

	const ElementId currentId = Sim_GetId(pSim, current);
	const ElementId targetId = Sim_GetId(pSim, target);

	const ElementMetadata *currentMetadata = ElementTable_Get(currentId);
	const ElementMetadata *targetMetadata = ElementTable_Get(targetId);

	const int currentDisplaceability = currentMetadata->displaceability;
	const int targetDisplaceability = targetMetadata->displaceability;

	if (targetDisplaceability <= currentDisplaceability)
		return false;

	return true;
}
