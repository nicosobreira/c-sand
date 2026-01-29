#pragma once

#include "gui/theme.h"
#include "simulation/sim.h"

#include "cache.h"

typedef struct SimRenderer
{
	SimRenderCache cache;
	Rectangle viewPort;
	float cellSize;
} SimRenderer;

void SimRenderer_Init(SimRenderer *pRender, Sim *pSim);

void SimRenderer_Free(SimRenderer *pRender);

void SimRenderer_Render(SimRenderer *pRender, Sim *pSim, const Theme *pTheme);

void SimRenderer_Resize(SimRenderer *pRender, Sim *pSim);
