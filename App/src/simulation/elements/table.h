/**
 * @file table.h
 * @brief Elements Jump Table
 */

#pragma once

#include <assert.h>

#include "id.h"
#include "template.h"

#include "simulation/sim.h"
/** Elements Metadata Jump Table.
 */
extern const ElementMetadata g_ElementTable[ELEMENT_TOTAL];

void ElementTable_Update(Sim *pSim);

/** Get ElementMetadata info
 * @param id Unkown ElementId (does not check)
 * @return A const pointer pointing to g_ElementTable id
 */
static inline const ElementMetadata *ElementTable_Get(ElementId id)
{
	assert(id >= 0 && id < ELEMENT_TOTAL);

	return &g_ElementTable[id];
}
