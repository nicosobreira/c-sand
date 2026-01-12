#include "cache.h"

#include <stddef.h>

#include "raylib.h"

void GridRenderCache_Init(GridRenderCache *cache, int width, int height)
{
	cache->width = width;
	cache->height = height;

	cache->pixels = MemAlloc((unsigned int)(width * height * sizeof(Color)));

	Image image = {
	    .data = cache->pixels,
	    .width = width,
	    .height = height,
	    .mipmaps = 1,
	    .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
	};

	cache->texture = LoadTextureFromImage(image);
}

void GridRenderCache_Free(GridRenderCache *cache)
{
	UnloadTexture(cache->texture);
	MemFree(cache->pixels);
	cache->pixels = NULL;
}
