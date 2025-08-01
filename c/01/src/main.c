#include "const.h"
#include "render/render.h"

int main() {
  // TODO: initialize this properly

  InitializeConstants();
  Arena frameArena =
      Arena_Init("frameArena", &frameStorage, FRAME_STORAGE_SIZE);

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
  Arena firstGenArena =
      Arena_Init("firstGenArena", &firstGenStorage, GEN_STORAGE_SIZE);
  Arena secondGenArena =
      Arena_Init("secondGenArena", &secondGenStorage, GEN_STORAGE_SIZE);

  Arena modeArena =
      Arena_Init("modeArena", &modeArenaStorage, MODE_STORAGE_SIZE);

  Render render = {.currentMode = RENDER_MODE_INIT,
                   .frameArena = &frameArena,
                   .firstGenArena = &firstGenArena,
                   .secondGenArena = &secondGenArena,
                   .modeArena = &modeArena};

  Render_Window(&render);
  return 0;
}
