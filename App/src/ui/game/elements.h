#pragma once

#include <stdbool.h>

#include "raylib.h"

#include "simulation/elements/id.h"
#include "ui/layout.h"
#include "ui/theme.h"

typedef struct ElementsUi
{
	ElementId current;
	Rectangle base;
	Layout layout;
	int fontSize;
} ElementsUi;

void ElementsUi_Init(ElementsUi *pUi);

void ElementsUi_Draw(ElementsUi *pUi, Theme *pTheme);
