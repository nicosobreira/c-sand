#pragma once

#include <stddef.h>
#include <stdint.h>

#include "raylib.h"

#include "simulation/sim_def.h"

/** Element simulation update function
 * @param pSim The sim
 * @param index Current Sim_Update index
 */
typedef void (*ElementUpdate)(Sim *pSim, int index);

typedef struct ElementMetadata
{
	const char *name;

	/** How easily this element is replaced by others.
	 * If another element with a lower value wants to replace the current once
	 * the lower value wins.
	 * Ranging between 0 and 100.
	 */
	uint8_t displaceability;

	/** How much heat affects this element.
	 * The smaller the value the less affected by heat.
	 * Ranging between 0 and 100.
	 */
	uint8_t ignation;
} ElementMetadata;

typedef struct ElementVisual
{
	Color color;
} ElementVisual;
