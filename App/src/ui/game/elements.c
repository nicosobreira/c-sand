#include "elements.h"

#include "raygui.h"

#include "simulation/elements/table.h"

void ElementsUi_Init(ElementsUi *pUi)
{
	const int height = pUi->fontSize + GROUP_PADDING;

	pUi->fontSize = 40;

	pUi->base = (Rectangle){
	    .x = GROUP_PADDING - 6,
	    .y = GetScreenHeight() - height - GROUP_PADDING + 6,
	    .width = 100,
	    .height = height,
	};
}

void ElementsUi_Draw(ElementsUi *pUi, Theme *pTheme)
{
	Rectangle rec = pUi->base;

	for (ElementId e = 0; e < ELEMENT_TOTAL; ++e)
	{
		if (GuiButton(rec, g_ElementTable[e].name))
		{
			pUi->current = e;
		}

		DrawRectangleRec(rec, Fade(pTheme->elements[e].color, 0.4f));

		rec.x += rec.width + GROUP_PADDING;
	}
}
