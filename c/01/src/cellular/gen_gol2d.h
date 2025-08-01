#ifndef GEN_GOL2D_H
#define GEN_GOL2D_H

#include <raylib.h>
#include "const.h"
#include "cells.h"

extern int CURRENT_GENERATION;

/*
 * Generate random values for each array
 */
void GeneratorGOL2D_InitializeCells(Cells2D *c2d);
/*
 * Iterates the given cells to the next generation.
 *
 * Ruleset (from wikipedia):
 * https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life): Any live cell with
 * fewer than two live neighbours dies, as if by underpopulation. Any live
 * cell with two or three live neighbours lives on to the next generation. Any
 * live cell with more than three live neighbours dies, as if by
 * overpopulation. Any dead cell with exactly three live neighbours becomes a
 * live cell, as if by reproduction.
 *
 */
void GeneratorGOL2D_NextGeneration(Cells2D *outC2d, Cells2D *inC2d);

#endif
