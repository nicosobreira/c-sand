#pragma once

#include <stdbool.h>

#include "table.h"

#include "sim/grid.h"

/** Check if the index bellow is valid
 * It first checks if target Index is valid then checks both elements
 * displaceability.
 * @param current Valid pGrid cell index
 * @param target Unkown cell index
 * @return True if move is valid, otherwise False
 */
bool isElementMoveValid(const Grid *pGrid, int current, int target);
