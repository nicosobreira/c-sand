#pragma once

#include <stddef.h>

#include "raylib.h"

typedef struct GridRenderCache
{
	Texture2D texture;
	Color *pixels;
	size_t totalPixels;
	int width;
	int height;
} GridRenderCache;

void GridRenderCache_Init(GridRenderCache *cache, int width, int height);

void GridRenderCache_Free(GridRenderCache *cache);
