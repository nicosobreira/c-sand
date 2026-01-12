#pragma once

#include <stddef.h>

#include "raylib.h"

#include "core/grid_def.h"

/** Element update function
 * @param pGrid The grid
 * @param index Current index
 */
typedef void (*ElementUpdate)(const Grid *pGrid, size_t index);

typedef struct ElementMetadata
{
	const char *name;
	ElementUpdate updateFunc;

	/// How easily this element is displaced by others.
	/// Ranging between 0 and 100
	int displaceability;
} ElementMetadata;

typedef struct ElementVisual
{
	Color color;
	char symbol;
} ElementVisual;
