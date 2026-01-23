#pragma once

#include "raylib.h"

#include "simulation/elements/id.h"
#include "simulation/elements/template.h"

typedef struct Theme
{
	ElementVisual elements[ELEMENT_TOTAL];
	Color backgrond;
	const char *name;
} Theme;

void Theme_Init(Theme *pTheme, const Theme *model);
