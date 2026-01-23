#pragma once

#include "render/sim/renderer.h"
#include "simulation/sim.h"
#include "ui/theme.h"

#include "scenes/scene.h"

typedef struct Simulation
{
	SimRenderer simRenderer;
	Sim sim;
	Theme theme;
	ElementId currentId;
} Simulation;

void Simulation_Init(Simulation *pSim);

void Simulation_Free(Simulation *pSim);

void Simulation_Update(Simulation *pSim, double delta);

void Simulation_Draw(Simulation *pSim);

void Simlation_Keyboard(Simulation *pSim);

void Simulation_Click(Simulation *pSim);

static inline void Simulation_Resize(Simulation *pSim)
{
	SimRenderer_Resize(&pSim->simRenderer, &pSim->sim);
}

Scene Simulation_Scene();
