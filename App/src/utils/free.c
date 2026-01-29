#include "free.h"

#include <stdlib.h>

void Pointer_Free(void **pp)
{
	if (!pp || !*pp)
		return;

	free(*pp);
	*pp = NULL;
}
