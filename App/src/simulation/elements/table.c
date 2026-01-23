#include "table.h"

#include "id.h"
#include "template.h"

#include "update/empty.h"
#include "update/lava.h"
#include "update/sand.h"
#include "update/water.h"

static const int defaultValue = 50;

const ElementMetadata g_ElementTable[ELEMENT_TOTAL] = {
    [ELEMENT_EMPTY] =
        {
            .name = "Empty",
            .updateFunc = update_Empty,
            .displaceability = 100,
            .ignation = 0,
        },
    [ELEMENT_SAND] =
        {
            .name = "Sand",
            .updateFunc = update_Sand,
            .displaceability = defaultValue,
            .ignation = 50,
        },
    [ELEMENT_WATER] =
        {
            .name = "Water",
            .updateFunc = update_Water,
            .displaceability = defaultValue,
            .ignation = 50,
        },
    [ELEMENT_STONE] =
        {
            .name = "Stone",
            .updateFunc = update_Empty,
            .displaceability = 0,
            .ignation = 0,
        },
    [ELEMENT_GLASS] =
        {
            .name = "Glass",
            .updateFunc = update_Empty,
            .displaceability = 0,
            .ignation = 0,
        },
    [ELEMENT_LAVA] = {
        .name = "Lava",
        .updateFunc = update_Lava,
        .displaceability = defaultValue,
        .ignation = 0,
    }
};
