#include "pause.h"

#include <stddef.h>

void Pause_Func(void *data)
{
	(void)data;
}

Scene Pause_Scene(void)
{
	void *data = NULL;

	Scene scene = {
	    .Init = Pause_Func,
	    .Free = Pause_Func,
	    .Update = Pause_Func,
	    .Draw = Pause_Func,
	    .pData = data,
	};

	return scene;
}
