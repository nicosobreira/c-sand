#pragma once

#include <stdint.h>

/** Numeric representation of an Element
 */
typedef enum _ElementId
{
	ELEMENT_EMPTY = 0,
	ELEMENT_SAND,
	ELEMENT_WATER,
	ELEMENT_STONE,
	ELEMENT_GLASS,
	ELEMENT_LAVA,
	ELEMENT_TOTAL
} _ElementId;

typedef uint8_t ElementId;
