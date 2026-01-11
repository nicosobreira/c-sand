#include "simulation.h"

#include <math.h>
#include <string.h>

#include "raylib.h"
#include "raymath.h"

void Simulation_Init(Simulation *pSim)
{
	memset(pSim, 0, sizeof(Simulation));

	Grid_Init(&pSim->grid, 100, 100);
	pSim->viewPort = (Rectangle){
	    .x = 10,
	    .y = 10,
	    .width = 200,
	    .height = 200,
	};

	Theme_Init(&pSim->theme, THEME_CATPPUCCIN_MOCHA);

	Simulation_Resize(pSim);
}

void Simulation_Update(Simulation *pSim, double delta)
{
	Grid_Update(&pSim->grid, delta);
}

void Simulation_Draw(Simulation *pSim);

void Simulation_Free(Simulation *pSim)
{
	Grid_Free(&pSim->grid);

	memset(pSim, 0, sizeof(Simulation));
}

void Simulation_Resize(Simulation *pSim)
{
	const float screenWidth = (float)GetScreenWidth();
	const float screenHeight = (float)GetScreenHeight();

	if (GetScreenWidth() < GetScreenHeight())
	{
		const float newWidth = screenWidth * 0.8f;
		pSim->cellSize = (int)(newWidth / (float)pSim->grid.width);
		pSim->viewPort.width = (float)pSim->cellSize * (float)pSim->grid.width;
		pSim->viewPort.height = (float)pSim->cellSize * (float)pSim->grid.height;
	}
	else
	{
		const float newHeight = screenHeight * 0.8f;
		pSim->cellSize = (int)(newHeight / (float)pSim->grid.height);
		pSim->viewPort.width = (float)pSim->cellSize * (float)pSim->grid.width;
		pSim->viewPort.height = (float)pSim->cellSize * (float)pSim->grid.height;
	}

	pSim->viewPort.x = 16;
	pSim->viewPort.y = (screenHeight - pSim->viewPort.height) / 2.0f;
}

void Simulation_Camera(Simulation *pSim)
{
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	{
		Vector2 delta = GetMouseDelta();
		delta = Vector2Scale(delta, -1.0f / pSim->camera.zoom);
		pSim->camera.target = Vector2Add(pSim->camera.target, delta);
	}

	if (GetMouseWheelMove() != 0.0f)
	{
		float scale = 0.1f * GetMouseWheelMove();
		float newZoom = Clamp(expf(logf(pSim->camera.zoom) + scale), 1.0f, 5.0f);

		if (pSim->camera.zoom == newZoom)
		{
			return;
		}

		pSim->camera.zoom = newZoom;

		TraceLog(LOG_DEBUG, "Zoom = %f", pSim->camera.zoom);
	}
}

void Simulation_Draw(Simulation *pSim)
{
	ClearBackground(pSim->theme.backgrond);

	Grid_Draw(&pSim->grid, &pSim->theme.cells, &pSim->viewPort, pSim->cellSize);

	DrawFPS(0, 0);
}

static bool isVectorInsideRectangle(Vector2 *pVec, Rectangle *pRect)
{
	float finalX = pRect->width + pRect->x;
	float finalY = pRect->height + pRect->y;

	if (pVec->x < pRect->x || pVec->x > finalX)
		return false;

	if (pVec->y < pRect->y || pVec->y > finalY)
		return false;

	return true;
}

void Simulation_Click(Simulation *pSim)
{
	if (!IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		return;

	Vector2 mouse = GetMousePosition();

	if (!isVectorInsideRectangle(&mouse, &pSim->viewPort))
		return;

	Vector2 mouseInView = Vector2Subtract(mouse, (Vector2){pSim->viewPort.x, pSim->viewPort.y});

	mouseInView.x /= (float)pSim->cellSize;
	mouseInView.y /= (float)pSim->cellSize;

	mouseInView.x = roundf(mouseInView.x);
	mouseInView.y = roundf(mouseInView.y);

	int index = Grid_GetIndex((int)mouseInView.y, (int)mouseInView.x, pSim->grid.width);

	pSim->grid.current[index] = CELL_SAND;
}
