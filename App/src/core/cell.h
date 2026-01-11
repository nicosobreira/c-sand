#pragma once

#include "raylib.h"

typedef enum CellType
{
	CELL_EMPTY = 0,
	CELL_SAND,
} CellType;

typedef struct CellsColors
{
	Color empty;
	Color sand;
} CellsColors;
