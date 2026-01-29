#pragma once

#include "id.h"

/** An Element with per cell data.
 */
typedef struct Element
{
	ElementId id;

	/// 0 - 255;
	int volume;
} Element;
