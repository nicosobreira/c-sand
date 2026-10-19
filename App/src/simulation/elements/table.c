#include "table.h"

#include "update/lava.h"
#include "update/sand.h"
#include "update/water.h"

#include "id.h"
#include "template.h"

static const uint8_t defaultValue = 50;

const ElementMetadata g_ElementTable[ELEMENT_TOTAL] = {
    [ELEMENT_EMPTY] =
        {
            .name = "Empty",
            .displaceability = 100,
            .ignation = 0,
        },
    [ELEMENT_SAND] =
        {
            .name = "Sand",
            .displaceability = defaultValue,
            .ignation = 50,
        },
    [ELEMENT_WATER] =
        {
            .name = "Water",
            .displaceability = defaultValue,
            .ignation = 50,
        },
    [ELEMENT_STONE] =
        {
            .name = "Stone",
            .displaceability = 0,
            .ignation = 0,
        },
    [ELEMENT_GLASS] =
        {
            .name = "Glass",
            .displaceability = 0,
            .ignation = 0,
        },
    [ELEMENT_LAVA] = {
        .name = "Lava",
        .displaceability = defaultValue,
        .ignation = 0,
    }
};

void ElementTable_Update(Sim *pSim)
{
	for (int i = pSim->size - 1; i >= 0; --i)
	// for (int i = pSim->size - 1; i >= 0; --i)
	{
		ElementId id = Sim_GetId(pSim, i);
		switch (Sim_GetId(pSim, i))
		{
		case ELEMENT_SAND:
			update_Sand(pSim, i);
			break;
		case ELEMENT_LAVA:
			update_Lava(pSim, i);
			break;
		case ELEMENT_WATER:
			update_Water(pSim, i);
			break;
		default:
			break;
		}
	}
}
