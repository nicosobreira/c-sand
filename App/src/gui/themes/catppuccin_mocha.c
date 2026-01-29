#include "catppuccin_mocha.h"

#include "simulation/elements/id.h"

const Theme Theme_CatpuccinMocha = {
    .name = "Catppuccin Mocha",
    .backgrond = {17, 17, 27, 255},
    .elements[ELEMENT_EMPTY] = {.color = {30, 30, 46, 255}},
    .elements[ELEMENT_SAND] = {.color = {249, 227, 161, 255}},
    .elements[ELEMENT_WATER] = {.color = {137, 180, 250, 255}},
    .elements[ELEMENT_STONE] = {.color = {108, 112, 134, 255}},
    .elements[ELEMENT_GLASS] = {.color = {245, 224, 220, 255}},
    .elements[ELEMENT_LAVA] = {.color = {250, 179, 135, 255}},
};
