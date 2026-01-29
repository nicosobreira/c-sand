#include "cache.h"

#include "raylib.h"

#include <stdlib.h>

#include "utils/free.h"

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
	    /// Raylib `Color` format
	    .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
	};

	cache->texture = LoadTextureFromImage(image);
	SetTextureFilter(cache->texture, TEXTURE_FILTER_POINT);
}

void SimRenderCache_Free(SimRenderCache *cache)
{
	UnloadTexture(cache->texture);
	FREE(cache->pixels);
}
