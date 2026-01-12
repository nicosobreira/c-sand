#pragma once

#include "clay.h"

typedef struct ButtonStyle
{
	Clay_Color normal;
	Clay_Color hover;
	Clay_Color pressed;
	int width;
	int height;
} ButtonStyle;

void ButtonComponent(const ButtonStyle *pStyle, const Clay_String *text);
