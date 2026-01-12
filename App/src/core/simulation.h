#pragma once

#include "raylib.h"

#include "core/grid.h"
#include "core/grid_cache.h"
#include "ui/theme.h"

typedef struct Simulation
{
	Grid grid;
	GridRenderCache gridCache;
	Camera2D camera;
	Theme theme;
	Rectangle viewPort;
	int cellSize;
} Simulation;

void Simulation_Init(Simulation *pSim);

void Simulation_Update(Simulation *pSim, double delta);

void Simulation_Draw(Simulation *pSim);

void Simulation_Free(Simulation *pSim);

void Simulation_Resize(Simulation *pSim);

void Simulation_Camera(Simulation *pSim);

void Simulation_Click(Simulation *pSim);
