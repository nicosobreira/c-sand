#pragma once

#include "simulation/sim.h"
#include "ui/theme.h"

#include "cache.h"

typedef struct SimRenderer
{
	SimRenderCache cache;
	Rectangle viewPort;
	float cellSize;
} SimRenderer;

void SimRenderer_Init(SimRenderer *pRender, Sim *pSim);

static inline void SimRenderer_Free(SimRenderer *pRender)
{
	SimRenderCache_Free(&pRender->cache);
}

void SimRenderer_Render(SimRenderer *pRender, Sim *pSim, const Theme *pTheme);

void SimRenderer_Resize(SimRenderer *pRender, Sim *pSim);
