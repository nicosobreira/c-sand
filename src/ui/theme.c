#include "theme.h"

static Theme catppuccinMocha = {
    .cells =
        {
            .empty = {30, 30, 46, 255},
            .sand = {249, 226, 175, 255},
        },
    .backgrond = {17, 17, 27, 255},
};

void Theme_Init(Theme *pTheme, ThemeId id)
{
	switch (id)
	{
	case THEME_CATPPUCCIN_MOCHA:
		*pTheme = catppuccinMocha;
		break;
	}
}
