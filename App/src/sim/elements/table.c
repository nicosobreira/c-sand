#include "table.h"

#include "id.h"
#include "template.h"

#include "update/empty.h"
#include "update/sand.h"
#include "update/water.h"

// clang-format off
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
		[ELEMENT_WATER] =
		{
			.name = "Water",
			.updateFunc = update_Water,
			.displaceability = 55,
		},
	};
// clang-format on
