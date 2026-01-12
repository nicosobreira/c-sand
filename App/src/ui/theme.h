#pragma once

#include "raylib.h"

#include "sim/elements/id.h"
#include "sim/elements/template.h"

typedef struct Theme
{
	ElementVisual elements[ELEMENT_TOTAL];
	Color backgrond;
	const char *name;
} Theme;

void Theme_Init(Theme *pTheme, Theme *model);
