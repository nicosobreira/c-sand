#pragma once

#include <stdint.h>

/** Numeric representation of an Element
 */
typedef enum ElementId_Value
{
	ELEMENT_EMPTY = 0,
	ELEMENT_SAND,
	ELEMENT_WATER,
	ELEMENT_STONE,
	ELEMENT_GLASS,
	ELEMENT_LAVA,
	ELEMENT_TOTAL
} ElementId_Value;

typedef uint8_t ElementId;
