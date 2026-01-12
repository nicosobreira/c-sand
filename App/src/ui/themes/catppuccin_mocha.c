#include "catppuccin_mocha.h"

#include "sim/elements/id.h"

extern Theme Theme_CatpuccinMocha;

Theme Theme_CatpuccinMocha = {
    .name = "Catppuccin Mocha",
    .backgrond = {17, 17, 27, 255},
    .elements[ELEMENT_EMPTY] = {.color = {30, 30, 46, 255}, .symbol = ' '},
    .elements[ELEMENT_SAND] = {.color = {249, 227, 161, 255}, .symbol = 'S'},
    .elements[ELEMENT_WATER] = {.color = {137, 180, 250, 255}, .symbol = 'W'},
};
