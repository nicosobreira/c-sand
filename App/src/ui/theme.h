#pragma once

#include "raylib.h"

#include "core/elements/id.h"
#include "core/elements/template.h"

typedef struct Theme
{
	ElementVisual elements[ELEMENT_TOTAL];
	Color backgrond;
	const char *name;
} Theme;

void Theme_Init(Theme *pTheme, Theme *model);
