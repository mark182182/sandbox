#include "gen_gol2d.h"
#include "const.h"
#include "cells.h"
#include <raylib.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <immintrin.h>

int CURRENT_GENERATION = 0;

void GeneratorGOL2D_InitializeCells(Cells2D *c2d, bool randomizeAlive) {
  int i = 0;
  for (int posX = 0; posX < SCREEN_WIDTH; posX += CELL_WIDTH_RATIO) {
    for (int posY = 0; posY < SCREEN_HEIGHT; posY += CELL_HEIGHT_RATIO) {
      if (randomizeAlive) {
        bool is_alive = rand() % CELL_INITIAL_GRID_DENSITY == 0;
        c2d->cells[i].is_alive = is_alive;
      } else {
        c2d->cells[i].is_alive = 0;
      }
      c2d->positionsX[i] = posX;
      c2d->positionsY[i] = posY;
      c2d->colors[i] = &RANDOM_COLORS[rand() % 2];
      i++;
    }
  }
}

const uint8_t UNDERPOPULATION_UPPER_CAP = 2;
const uint8_t OVERPOPULATION_UPPER_CAP = 3;

// TODO: use a compute shader instead (since OpenGL 4.3)
// possibly binding the 2 SSBOs and call glDispatchCompute and glMemoryBarrier
void GeneratorGOL2D_NextGeneration(Cells2D *outC2d, Cells2D *inC2d) {
  for (int i = 0; i < CELL_COUNT; i++) {
    int neighbours = __CheckNeighbours(inC2d, i);
    // under or overpopulation
    if (neighbours < UNDERPOPULATION_UPPER_CAP ||
        neighbours > OVERPOPULATION_UPPER_CAP) {
      outC2d->cells[i].is_alive = false;
      // reproduction
    } else if (!inC2d->cells[i].is_alive &&
               neighbours == OVERPOPULATION_UPPER_CAP) {
      outC2d->cells[i].is_alive = true;
    }
  }
  CURRENT_GENERATION++;
}

/**
 * Counts the neighbours for the given cell.
 * Every cell interacts with its eight neighbours, which are the cells that
 * are horizontally, vertically, or diagonally adjacent.
 *
 * @return int: the number of neighbours
 */
int __CheckNeighbours(Cells2D *inputCells, int i) {
  int neighbours = 0;
  int arraySize = (CELL_COUNT - 1);

  for (int j = 0; j < CELL_NEIGHBOUR_SIZE; j++) {
    int relativeIdx = i + DIAGONAL_INDEXES[j];
    if (relativeIdx >= 0 && relativeIdx <= arraySize &&
        inputCells->cells[relativeIdx].is_alive) {
      // the relative diagonal cell
      neighbours++;
    }
  }

  for (int j = 0; j < CELL_NEIGHBOUR_SIZE; j++) {
    int relativeIdx = i + ADJECENT_INDEXES[j];
    if (relativeIdx >= 0 && relativeIdx <= arraySize &&
        inputCells->cells[relativeIdx].is_alive) {
      // the adjecent diagonal cell
      neighbours++;
    }
  }

  return neighbours;
}
