#pragma once

#include <stdint.h>

#include "simulation/elements/id.h"

/** An Element with per cell data.
 */
typedef struct Particle
{
	ElementId id;

	/// 0 - 255;
	int volume;
} Particle;
