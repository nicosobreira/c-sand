#pragma once

#include <stdbool.h>

#include "simulation/sim.h"

/** Check if the index bellow is valid
 * It first checks if target Index is valid then checks both elements
 * displaceability.
 * @param current Valid pSim cell index
 * @param target Unkown cell index
 * @return True if move is valid, otherwise False
 */
bool isElementMoveValid(Sim *pSim, int current, int target);
