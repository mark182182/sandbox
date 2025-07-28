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

void Cells2D_InitArraysBasedOnCellSize(Arena *arena, Cells2D *cd) {
  Cell *cells = Arena_AllocAligned(arena, CELL_COUNT, DEFAULT_ARENA_ALIGNMENT);
  assert((!cells, "Unable to allocate cells"));

  cd->cells = cells;

  int *positionsX =
      Arena_AllocAligned(arena, CELL_COUNT, DEFAULT_ARENA_ALIGNMENT);
  cd->positionsX = positionsX;

  int *positionsY =
      Arena_AllocAligned(arena, CELL_COUNT, DEFAULT_ARENA_ALIGNMENT);
  cd->positionsY = positionsY;

  Color **colors =
      Arena_AllocAligned(arena, CELL_COUNT, DEFAULT_ARENA_ALIGNMENT);
  cd->colors = colors;
}

// // TODO: Use arena allocator instead
// void Cells2D_FreeArrays(Cells2D *cd) {
//   if (cd->cells != nullptr) {
//     _mm_free(cd->cells);
//   }

//   if (cd->positionsX != nullptr) {
//     delete cd->positionsX;
//   }
//   if (cd->positionsY != nullptr) {
//     delete cd->positionsY;
//   }
//   if (cd->colors != nullptr) {
//     delete cd->colors;
//   }
// }

/**
Use arena allocator instead of _malloc and _mm_free

MemoryArena worldA = AllocateArena(WORLD_SIZE);
MemoryArena worldB = AllocateArena(WORLD_SIZE);

MemoryArena* current = &worldA;
MemoryArena* next    = &worldB;

while (running) {
    SimulateGameOfLife(current, next);
    RenderFrame(next);

    // Swap arenas
    MemoryArena* temp = current;
    current = next;
    next = temp;

    ResetArena(next); // clear the one we�ll write into next frame
}

Yes, it does allocate roughly twice the memory upfront�one full arena buffer per
"frame state." But this is intentional and typical for double buffering:
- You pay the memory cost once at initialization.
- No per-frame malloc/free overhead.
- No expensive deep copies each frame.
- You get predictable, linear memory access and fast pointer swaps.


Why This Memory Tradeoff Is Worth It
Approach                    Memory Usage        CPU Overhead per Frame
Complexity Single arena + deep copy    1x + copy buffer	High (copy each frame)
Complex, slower Double buffer arenas	    2x memory upfront	Minimal (just
swap)     Simple, fast
**/

// TODO: Fix after there is a working arena allocator implementation
// Cells2D *Cells2D_DeepCopyCells(Cells2D *originalCd) {
//   Cell *newCells = (Cell *)_mm_malloc(CELL_COUNT * sizeof(Cell), 32);
//   if (!newCells) {
//     throw std::bad_alloc();
//   }

//   for (int i = 0; i < CELL_COUNT; i++) {
//     new (&newCells[i]) Cell();
//     (&newCells[i])->is_alive = (&originalCd->cells[i])->is_alive;
//   }

//   Cells2D *newCd = new Cells2D;
//   newCd->cells = newCells;
//   newCd->positionsX = nullptr;
//   newCd->positionsY = nullptr;
//   newCd->colors = nullptr;
//   return newCd;
// }