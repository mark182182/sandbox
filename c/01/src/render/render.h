#ifndef RENDERER_H
#define RENDERER_H

#include "arena.h"

typedef enum RenderMode {
  RENDER_MODE_INIT,
  RENDER_MODE_2D,
  RENDER_MODE_3D,
  MAX_RENDER_MODE
} RenderMode;

typedef struct Render {
  // cleared at every mode's end; e.g 2D or 3D
  Arena *modeArena;
  /*
   * Cleared at the end of every second generation (counting from intial), where
   * based on the rule the cellular automata should reset the previous
   * generation's cells and store the current generation's cells.
   *
   * This means that depending on the current generation, either the first or
   * the second generation arena's cells will be rendered. This method in
   * essency is similar to double buffering.
   *
   * Initial state (0. generation):
   * 1. generation cells: allocates the memory
   * 2. generation cells: does not allocate
   *
   * At 1. generation:
   * 2. generation cells: allocates memory, sets the state based on the rule
   * 1. generation cells: memory gets reset
   *
   * At 2. generation:
   * 1. generation cells: allocates memory, sets the state based on the rule
   * 2. generation cells: memory gets reset
   *
   * ...
   *
   * At n. generation:
   * n+1 cells: allocates memory, sets the state based on the rule
   * n cells: generation: memory gets reset
   */
  Arena *firstGenArena;
  Arena *secondGenArena;

  // cleared at every frame
  Arena *frameArena;

  RenderMode currentMode;

} Render;

void Render_Window(Render *renderer);
void Render_TeardownAfterWindow(Render *renderer);

#endif