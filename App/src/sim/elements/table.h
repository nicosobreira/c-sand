#pragma once

#include <assert.h>

#include "id.h"
#include "template.h"

#include "sim/grid.h"

extern const ElementMetadata g_ElementTable[ELEMENT_TOTAL];

static inline void ElementTable_Update(Grid *pGrid, int index)
{
	const ElementId id = pGrid->current[index];
	g_ElementTable[id].updateFunc(pGrid, index);
}

/** Get ElementMetadata info
 * @param id Unkown ElementId (does not check)
 * @return A const pointer pointing to g_ElementTable id
 */
static inline const ElementMetadata *ElementTable_Get(ElementId id)
{
	assert(id >= 0 && id < ELEMENT_TOTAL);

	return &g_ElementTable[id];
}
