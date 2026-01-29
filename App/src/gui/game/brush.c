#include "brush.h"

#include "raylib.h"

static int size = 25;
static BrushType type = BRUSH_SQUARE;

static int clamp(int value, int min, int max)
{
	if (value <= min)
		return min;

	if (value >= max)
		return max;

	return value;
}

void Brush_Draw(Brush *pBrush)
{
	(void)pBrush;

	int wheel = GetMouseWheelMove();
	if (wheel != 0)
	{
		size += wheel;
		size = clamp(size, 1, 25);
	}

	const Color inside = Fade(WHITE, 0.1f);
	const Color outline = GRAY;

	switch (type)
	{
	case BRUSH_CIRCLE:
		DrawCircle(GetMouseX(), GetMouseY(), size, inside);
		DrawCircleLines(GetMouseX(), GetMouseY(), size, outline);
		break;
	case BRUSH_SQUARE:
		DrawRectangle(GetMouseX() - size / 2, GetMouseY() - size / 2, size, size, inside);
		DrawRectangleLines(GetMouseX() - size / 2, GetMouseY() - size / 2, size, size, outline);
		break;
	}
}
