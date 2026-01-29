#pragma once

#include <stddef.h>

typedef struct GuiNode
{
	/// Array of pointers.
	struct GuiNode **leafs;

	/// Size of `leafs` array.
	size_t sizeLeafs;

	int x;
	int y;
} GuiNode;
