#include "simulation.h"

#include <math.h>
#include <string.h>

#include "clay.h"
#include "clay_renderer_raylib.h"
#include "raylib.h"
#include "raymath.h"

#include "core/grid.h"
#include "ui/button.h"

#include "ui/themes/catppuccin_mocha.h"

void Simulation_Init(Simulation *pSim)
{
	memset(pSim, 0, sizeof(Simulation));

	const int defaultWidth = 1024 / 2;
	const int defaultHeight = 560 / 2;

	Grid_Init(&pSim->grid, defaultWidth, defaultHeight);
	GridRenderCache_Init(&pSim->gridCache, defaultWidth, defaultHeight);

	Theme_Init(&pSim->theme, &Theme_CatpuccinMocha);

	Simulation_Resize(pSim);
}

void Simulation_Update(Simulation *pSim, double delta)
{
	Grid_Update(&pSim->grid, delta);
}

void Simulation_Free(Simulation *pSim)
{
	Grid_Free(&pSim->grid);
	GridRenderCache_Free(&pSim->gridCache);

	memset(pSim, 0, sizeof(Simulation));
}

// FIX: Screen Rezing don't work
void Simulation_Resize(Simulation *pSim)
{
	const float screenWidth = (float)GetScreenWidth();
	const float screenHeight = (float)GetScreenHeight();

	float cellSize = 0;

	if (screenWidth < screenHeight)
	{
		cellSize = screenWidth / (float)pSim->grid.width;
		pSim->viewPort.width = pSim->cellSize * (float)pSim->grid.width;
		pSim->viewPort.height = pSim->cellSize * (float)pSim->grid.height;
	}
	else
	{
		cellSize = screenHeight / (float)pSim->grid.height;
		pSim->viewPort.width = cellSize * (float)pSim->grid.width;
		pSim->viewPort.height = cellSize * (float)pSim->grid.height;
	}

	// BUG: Why is this equal to zero?
	pSim->cellSize = cellSize;

	pSim->viewPort.x = (screenWidth - pSim->viewPort.width) / 2.0f;
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

	Clay_BeginLayout();

	const ButtonStyle button = {
	    .normal = {255, 0, 0, 255},
	    .hover = {0, 255, 0, 255},
	    .pressed = {0, 0, 255, 255},
	    .width = 50,
	    .height = 30,
	};

	CLAY(
	    CLAY_ID("Root"),
	    {.layout = {
	         .layoutDirection = CLAY_TOP_TO_BOTTOM,
	         .sizing = {CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0)},
	         .padding = CLAY_PADDING_ALL(10)
	     }}
	)
	{
		CLAY(
		    CLAY_ID("Spacer"),
		    {.layout = {
		         .sizing = {CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(1)},
		     }}
		)
		{
		}
		CLAY(
		    CLAY_ID("Elements"), // Bottom row
		    {.layout = {
		         .layoutDirection = CLAY_LEFT_TO_RIGHT,
		         .childAlignment = {.x = CLAY_ALIGN_X_RIGHT},
		         .childGap = 16,
		         .sizing = {CLAY_SIZING_GROW(0), CLAY_SIZING_FIXED(button.height)},
		     }}
		)
		{
			CLAY(
			    CLAY_ID("Button"),
			    {.layout = {.sizing = {.width = button.width, .height = button.height}},
			     .backgroundColor = Clay_Hovered() ? button.hover : button.normal}
			)
			{
				// CLAY_TEXT(CLAY_STRING("Button"), CLAY_TEXT_CONFIG({.fontSize = 16}));
			}
		}
	}

	Clay_RenderCommandArray renderCommands = Clay_EndLayout();

	Grid_Draw(&pSim->grid, &pSim->theme, &pSim->viewPort, pSim->cellSize, &pSim->gridCache);

	Clay_Raylib_Render(renderCommands, NULL);

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

	pSim->grid.current[index] = ELEMENT_SAND;
}
