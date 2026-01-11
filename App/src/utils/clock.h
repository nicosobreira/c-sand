#pragma once

#include <stdbool.h>

/// The delta time sets the clock's time unit
typedef struct Clock
{
	double target;
	double previous;
	double total;
} Clock;

double Clock_Get(Clock *pClock);

void Clock_Set(Clock *pClock, double target);

/** Update clock based on a delta time
 * @return true and reset the clock if it ends, false otherwise.
 */
bool Clock_Tick(Clock *pClock, double delta);

void Clock_Reset(Clock *pClock);
