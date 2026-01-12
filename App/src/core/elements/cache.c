#include "cache.h"

#include "id.h"
#include "template.h"

#include "update/empty.h"
#include "update/sand.h"

// clang-format off
const ElementUpdate g_ElementUpdate[ELEMENT_TOTAL] = {
	[ELEMENT_EMPTY] = update_Empty,
	[ELEMENT_SAND] = update_Sand,
};

const ElementMetadata g_ElementTable[ELEMENT_TOTAL] =
	{
		[ELEMENT_EMPTY] =
		{
			.name = "Empty",
			.updateFunc = update_Empty,
			.displaceability = 100,
		},
		[ELEMENT_SAND] =
		{
			.name = "Sand",
			.updateFunc = update_Sand,
			.displaceability = 50,
		},
	};
// clang-format on
