#include "clock.h"

double Clock_Get(Clock *pClock)
{
	return pClock->total;
}

void Clock_Set(Clock *pClock, double target)
{
	pClock->target = target;
	pClock->total = 0.0;
	Clock_Reset(pClock);
}

bool Clock_Tick(Clock *pClock, double delta)
{
	pClock->previous += delta;

	if (pClock->previous >= pClock->target)
	{
		pClock->total += pClock->previous;
		Clock_Reset(pClock);
		return true;
	}

	return false;
}

void Clock_Reset(Clock *pClock)
{
	pClock->previous = 0;
}
