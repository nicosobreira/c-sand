#pragma once

#include <stdbool.h>

#include "raylib.h"

#include "gui/layout.h"
#include "gui/theme.h"
#include "simulation/elements/id.h"

typedef struct ElementsUi
{
	ElementId current;
	Rectangle base;
	Layout layout;
	int fontSize;
} ElementsUi;

void ElementsUi_Init(ElementsUi *pUi);

void ElementsUi_Draw(ElementsUi *pUi, Theme *pTheme);
