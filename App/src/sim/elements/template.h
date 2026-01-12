#pragma once

#include <stddef.h>

#include "raylib.h"

#include "sim/grid_def.h"

/** Element simulation update function
 * @param pGrid The grid
 * @param index Current Grid_Update index
 */
typedef void (*ElementUpdate)(Grid *pGrid, int index);

typedef struct ElementMetadata
{
	const char *name;
	ElementUpdate updateFunc;

	/** How easily this element is displaced by others.
	 * If another element with a lower value wants to replace the current once
	 * the lower value wins.
	 * Ranging between 0 and 100.
	 */
	int displaceability;
} ElementMetadata;

typedef struct ElementVisual
{
	Color color;
	char symbol;
} ElementVisual;
