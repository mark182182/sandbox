#ifndef CELLS_H
#define CELLS_H

#include "const.h"
#include "stdint.h"

// TODO: These should come from a config file
const int CELL_HEIGHT_RATIO = 1 << 3; // power of two is recommended
const int CELL_WIDTH_RATIO = 1 << 3;  // power of two is recommended
const int INITIAL_FREQUENCY = 5;

const int CELL_HEIGHT_SIZE = DEFAULT_CONST.SCREEN_HEIGHT / CELL_HEIGHT_RATIO;
const int CELL_WIDTH_SIZE = DEFAULT_CONST.SCREEN_WIDTH / CELL_WIDTH_RATIO;
const int CELL_COUNT = CELL_HEIGHT_SIZE * CELL_WIDTH_SIZE;

const uint8_t CELL_INDEX_SIZE = 4;

/*
 * Diagonals relative to the current cell, e.g. if the ratio is 10:
 * top-left  bottom-left bottom-right    top-right
 * -72 - 1   -72 + 1     +72 - 1         +72 + 1
 */

const int DIAGONAL_INDEXES[CELL_INDEX_SIZE] = {
    (-1 * CELL_HEIGHT_SIZE) - 1, (-1 * CELL_HEIGHT_SIZE) + 1,
    CELL_HEIGHT_SIZE - 1, CELL_HEIGHT_SIZE + 1};
/*
 * Adjecent relative idx to the current cell, e.g. if the ratio is 10:
 * top   bottom  left    right
 * -1    +1      -72     +72
 */
const int ADJECENT_INDEXES[CELL_INDEX_SIZE] = {-1, +1, (-1 * CELL_HEIGHT_SIZE),
                                               CELL_HEIGHT_SIZE};

typedef struct Cell {
  bool is_alive; // populated or unpopulated
} Cell;

/*
 * SOA based container for cells to be drawn on the screen in 2D. The cells are
 * stored in height by width in one continous memory block, from top to bottom.
 *
 * The actual cell values (0 or 1) represent the populated/unpopulated cells.
 * E.g. alignment:
 *   x012
 * y ____
 * 0|1100|
 * 1|0111|
 * 2|1001|
 * ........
 */
typedef struct Cells2D {
  Cell *cells;
  int *positionsX;
  int *positionsY;
  Color **colors;
} Cells2D;

/*
 * Creates a deep copy of the given Cells2D and returns its pointer.
 */
Cells2D *Cells2D_DeepCopyCells(Cells2D *originalCd);

void Cells2D_InitArraysBasedOnCellSize(Cells2D *cd);
void Cells2D_FreeArrays(Cells2D *cd);

#endif