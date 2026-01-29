#include "renderer.h"

#include <math.h>

void SimRenderer_Init(SimRenderer *pRender, Sim *pSim)
{
	SimRenderCache_Init(&pRender->cache, pSim->width, pSim->height);

	SimRenderer_Resize(pRender, pSim);
}

void SimRenderer_Free(SimRenderer *pRender)
{
	SimRenderCache_Free(&pRender->cache);
}

void SimRenderer_Render(SimRenderer *pRender, Sim *pSim, const Theme *pTheme)
{
	SimRenderCache *pCache = &pRender->cache;
	Rectangle *pView = &pRender->viewPort;
	float cellSize = pRender->cellSize;

	for (size_t i = 0; i < pCache->totalPixels; ++i)
	{
		ElementId e = Sim_GetId(pSim, i);
		pCache->pixels[i] = pTheme->elements[e].color;
	}

	UpdateTexture(pCache->texture, pCache->pixels);

	// Draw texture ONCE (scaled)
	DrawTextureEx(pCache->texture, (Vector2){pView->x, pView->y}, 0.0f, cellSize, WHITE);
}

/** Assert that a number is even
 */
static float evenFloat(float a)
{
	return roundf(a * 0.5f) * 2.0f;
}

void SimRenderer_Resize(SimRenderer *pRender, Sim *pSim)
{
	Rectangle *pView = &pRender->viewPort;

	const float screenWidth = (float)GetScreenWidth();
	const float screenHeight = (float)GetScreenHeight();

	float cellSize = 0;

	if (screenWidth < screenHeight)
	{
		cellSize = evenFloat(screenWidth / (float)pSim->width);
		pView->width = pRender->cellSize * (float)pSim->width;
		pView->height = pRender->cellSize * (float)pSim->height;
	}
	else
	{
		cellSize = evenFloat(screenHeight / (float)pSim->height);
		pView->width = cellSize * (float)pSim->width;
		pView->height = cellSize * (float)pSim->height;
	}

	pRender->cellSize = cellSize;

	pView->x = (screenWidth - pView->width) / 2.0f;
	pView->y = (screenHeight - pView->height) / 2.0f;

	TraceLog(LOG_DEBUG, "%f", cellSize);
}
