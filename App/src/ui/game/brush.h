#pragma once

typedef enum BrushType
{
	BRUSH_CIRCLE,
	BRUSH_SQUARE,
} BrushType;

typedef struct Brush
{
	BrushType type;
	int radius;
} Brush;

void Brush_Init(Brush *pBrush);

/// Draw brush outline with the current Cursor position
void Brush_Draw(Brush *pBrush);

void Brush_OnClick(Brush *pBrush);

void Brush_OnScrool(Brush *pBrush);

void Brush_Resize(Brush *pBrush, int newRadius);
