#pragma once

#include <stdbool.h>

#include "simulation/sim.h"

/** Check if the index bellow is valid
 * It first checks if target index is valid then if the index in occupied on
 * both current and next buffers
 * @param target Unkown cell index
 * @retval true Valid move
 * @retval false Invalid move
 */
bool isElementMoveValid(Sim *pSim, int target);
