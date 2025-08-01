#include "gen_gol2d.h"
#include "const.h"
#include "cells.h"
#include <raylib.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <immintrin.h>
#include "dstructs/arena.h"
#include <assert.h>

/*
 * Diagonals relative to the current cell, e.g. if the ratio is 10:
 * top-left  bottom-left bottom-right    top-right
 * -72 - 1   -72 + 1     +72 - 1         +72 + 1
 */
const int DIAGONAL_INDEXES[] = {(-1 * CELL_HEIGHT_SIZE) - 1,
                                (-1 * CELL_HEIGHT_SIZE) + 1,
                                CELL_HEIGHT_SIZE - 1, CELL_HEIGHT_SIZE + 1};

/*
 * Adjecent relative idx to the current cell, e.g. if the ratio is 10:
 * top   bottom  left    right
 * -1    +1      -72     +72
 */
const int ADJECENT_INDEXES[] = {-1, +1, (-1 * CELL_HEIGHT_SIZE),
                                CELL_HEIGHT_SIZE};

void Cells2D_InitArraysBasedOnCellSize(Arena *arena, Cells2D *c2d) {
  Cell *cells = Arena_AllocAlignedZeroed(arena, CELL_COUNT * sizeof(Cell),
                                         DEFAULT_ARENA_ALIGNMENT);

  c2d->cells = cells;

  int *positionsX = Arena_AllocAlignedZeroed(arena, CELL_COUNT * sizeof(int),
                                             DEFAULT_ARENA_ALIGNMENT);
  c2d->positionsX = positionsX;

  int *positionsY = Arena_AllocAlignedZeroed(arena, CELL_COUNT * sizeof(int),
                                             DEFAULT_ARENA_ALIGNMENT);
  c2d->positionsY = positionsY;

  Color **colors = Arena_AllocAlignedZeroed(arena, CELL_COUNT * sizeof(Color *),
                                            DEFAULT_ARENA_ALIGNMENT);
  c2d->colors = colors;
}