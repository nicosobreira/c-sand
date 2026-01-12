#pragma once

#include <assert.h>

#include "id.h"
#include "template.h"

extern const ElementUpdate g_ElementUpdate[ELEMENT_TOTAL];

extern const ElementMetadata g_ElementTable[ELEMENT_TOTAL];

/** Get ElementMetadata info
 * @param id Unkown ElementId (does not check)
 * @return A const pointer pointing to g_ElementTable id
 */
static inline const ElementMetadata *ElementTable_Get(ElementId id)
{
	assert(id >= 0 && id < ELEMENT_TOTAL);

	return &g_ElementTable[id];
}
