#include "table.h"

#include "id.h"
#include "template.h"

#include "update/empty.h"
#include "update/sand.h"
#include "update/stone.h"
#include "update/water.h"

static const int defaultDisplaceability = 50;

const ElementMetadata g_ElementTable[ELEMENT_TOTAL] = {
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
            .displaceability = defaultDisplaceability,
        },
    [ELEMENT_WATER] =
        {
            .name = "Water",
            .updateFunc = update_Water,
            .displaceability = defaultDisplaceability,
        },
    [ELEMENT_STONE] = {
        .name = "Stone",
        .updateFunc = update_Stone,
        .displaceability = defaultDisplaceability,
    },
};
