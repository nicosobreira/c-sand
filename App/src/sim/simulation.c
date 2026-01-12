#include "simulation.h"

#include <math.h>
#include <string.h>

#include "clay.h"
#include "clay_renderer_raylib.h"
#include "raylib.h"
#include "raymath.h"

#include "sim/grid.h"
#include "ui/button.h"

#include "ui/themes/catppuccin_mocha.h"

void Simulation_Init(Simulation *pSim)
{
	memset(pSim, 0, sizeof(Simulation));

	const int defaultWidth = 512;
	const int defaultHeight = 280;

	Grid_Init(&pSim->grid, defaultWidth, defaultHeight);

	Theme_Init(&pSim->theme, &Theme_CatpuccinMocha);

	GridRenderer_Init(&pSim->gridRenderer, &pSim->grid);

	GridRenderer_Resize(&pSim->gridRenderer, &pSim->grid);
}

void Simulation_Update(Simulation *pSim, double delta)
{
	Grid_Update(&pSim->grid, delta);
}

void Simulation_Free(Simulation *pSim)
{
	Grid_Free(&pSim->grid);

	memset(pSim, 0, sizeof(Simulation));
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

	GridRenderer_Render(&pSim->gridRenderer, &pSim->grid, &pSim->theme);

	Clay_Raylib_Render(renderCommands, NULL);

	DrawFPS(0, 0);
}

void Simlation_Keyboard(Simulation *pSim)
{
	if (IsKeyPressed(KEY_ONE))
	{
		pSim->currentId = ELEMENT_SAND;
	}
	else if (IsKeyPressed(KEY_TWO))
	{
		pSim->currentId = ELEMENT_WATER;
	}
	else if (IsKeyPressed(KEY_ZERO))
	{
		pSim->currentId = ELEMENT_EMPTY;
	}
}

void Simulation_Click(Simulation *pSim)
{
	Rectangle *pView = &pSim->gridRenderer.viewPort;
	float cellSize = (float)pSim->gridRenderer.cellSize;

	if (!IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		return;

	Vector2 mouse = GetMousePosition();

	if (!CheckCollisionPointRec(mouse, *pView))
		return;

	Vector2 mouseInView = Vector2Subtract(mouse, (Vector2){pView->x, pView->y});

	mouseInView.x /= cellSize;
	mouseInView.y /= cellSize;

	mouseInView.x = roundf(mouseInView.x);
	mouseInView.y = roundf(mouseInView.y);

	int index = Grid_GetIndex((int)mouseInView.y, (int)mouseInView.x, pSim->grid.width);

	pSim->grid.current[index] = pSim->currentId;
}
