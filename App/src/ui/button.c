#include "button.h"

void ButtonComponent(const ButtonStyle *pStyle, const Clay_String *text)
{
	CLAY_AUTO_ID({.layout = {.sizing = {pStyle->width, pStyle->height}}, .backgroundColor = pStyle->normal})
	{
		CLAY_TEXT(*text, CLAY_TEXT_CONFIG({.fontSize = 16}));
	}
}
