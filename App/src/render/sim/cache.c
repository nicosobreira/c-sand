#include "cache.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"

void SimRenderCache_Init(SimRenderCache *cache, int width, int height)
{
	cache->width = width;
	cache->height = height;

	cache->totalPixels = width * height;

	cache->pixels = malloc((size_t)(cache->totalPixels * sizeof(Color)));

	Image image = {
	    .data = cache->pixels,
	    .width = width,
	    .height = height,
	    .mipmaps = 1,
	    .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
	};

	cache->texture = LoadTextureFromImage(image);
}

void SimRenderCache_Free(SimRenderCache *cache)
{
	UnloadTexture(cache->texture);
	free(cache->pixels);

	memset(cache, 0, sizeof(SimRenderCache));
}
