#pragma once

#include "raylib.h"

#include "simulation/grid.h"

typedef struct Simulation
{
	Grid grid;
	Camera2D camera;
} Simulation;

void Simulation_Init(Simulation *pSim);
