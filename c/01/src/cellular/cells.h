#ifndef CELLS_H
#define CELLS_H

#include "const.h"
#include "stdint.h"

static const int CELL_HEIGHT_RATIO = 8; // power of two is recommended
static const int CELL_WIDTH_RATIO = 8;  // power of two is recommended
static const int CELL_INITIAL_FREQUENCY = 5;
static const int CELL_HEIGHT_SIZE = SCREEN_HEIGHT / CELL_HEIGHT_RATIO;
static const int CELL_WIDTH_SIZE = SCREEN_WIDTH / CELL_WIDTH_RATIO;
const int CELL_COUNT = CELL_HEIGHT_SIZE * CELL_WIDTH_SIZE;

extern const int CELL_HEIGHT_RATIO;
extern const int CELL_WIDTH_RATIO;
extern const int INITIAL_FREQUENCY;

extern const int CELL_HEIGHT_SIZE;
extern const int CELL_WIDTH_SIZE;
extern const int CELL_COUNT;

extern const uint8_t CELL_INDEX_SIZE;

extern const int DIAGONAL_INDEXES[];
extern const int ADJECENT_INDEXES[];

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