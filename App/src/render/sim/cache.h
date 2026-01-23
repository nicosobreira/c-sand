#pragma once

#include <stddef.h>

#include "raylib.h"

typedef struct SimRenderCache
{
	Texture2D texture;
	Color *pixels;
	size_t totalPixels;
	int width;
	int height;
} SimRenderCache;

void SimRenderCache_Init(SimRenderCache *cache, int width, int height);

void SimRenderCache_Free(SimRenderCache *cache);
