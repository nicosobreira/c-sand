#pragma once

#include "render/grid/renderer.h"
#include "sim/grid.h"
#include "ui/theme.h"

typedef struct Simulation
{
	GridRenderer gridRenderer;
	Grid grid;
	Theme theme;
} Simulation;

void Simulation_Init(Simulation *pSim);

void Simulation_Free(Simulation *pSim);

void Simulation_Update(Simulation *pSim, double delta);

void Simulation_Draw(Simulation *pSim);

void Simulation_Click(Simulation *pSim);

static inline void Simulation_Resize(Simulation *pSim)
{
	GridRenderer_Resize(&pSim->gridRenderer, &pSim->grid);
}
