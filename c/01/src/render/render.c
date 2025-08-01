#include "render.h"
#include "font.h"
#include "cellular/gen_gol2d.h"

#include <assert.h>
#include <raylib.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include "const.h"
#include "menu.h"
#include <time.h>

void Render_Window(Render *render) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "CA Renderer");

  // load any long living resources here
  Menu menu = Menu_Init();

  bool isWireframeMode = false;
  int pressed = 0;
  bool isPaused = false;
  float deltaTime = 0;
  int fpsCap = 60;
  SetTargetFPS(fpsCap);

  Cells2D firstCd = {0};
  Cells2D secondCd = {0};

  Cells2D_InitArraysBasedOnCellSize(render->firstGenArena, &firstCd);
  Cells2D_InitArraysBasedOnCellSize(render->secondGenArena, &secondCd);

  GeneratorGOL2D_InitializeCells(&firstCd, true);
  GeneratorGOL2D_InitializeCells(&secondCd, false);

  while (!WindowShouldClose() && pressed != 'q') {
    ClearBackground(WHITE);

    // update variables here
    Menu_Update(&menu);

    pressed = GetCharPressed();

    if (fpsCap == 60 && pressed == 'c') {
      fpsCap = 0;
      SetTargetFPS(fpsCap);
    } else if (fpsCap == 0 && pressed == 'c') {
      fpsCap = 60;
      SetTargetFPS(fpsCap);
    }

    if (!isWireframeMode && pressed == 't') {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      isWireframeMode = true;
    } else if (isWireframeMode && pressed == 't') {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      isWireframeMode = false;
    }

    // would implement batched rendering, draw calls here, if needed

    BeginDrawing();

    if (pressed == 'r') {
      GeneratorGOL2D_InitializeCells(&firstCd, true);
      GeneratorGOL2D_InitializeCells(&secondCd, false);
      CURRENT_GENERATION = 0;
    }

    if (pressed == 'p') {
      isPaused = !isPaused;
    }

    // TODO: The simulation is not working properly, because even for the
    // initial state to go on to the next generation some cells need to be
    // alive, in order for the whole grid not to die out.

    if (isPaused == 0) {
      clock_t time = clock();
      if (CURRENT_GENERATION != 0) {
        if (CURRENT_GENERATION % 2 == 0) {
          // TODO: For some reason, the first generation will be rendered
          // correctly, but any subsequent (due to reset issues possibly)
          // generation will be not.
          GeneratorGOL2D_NextGeneration(&firstCd, &secondCd);
          __Render_ResetCells(render->secondGenArena, &secondCd);
        } else {
          GeneratorGOL2D_NextGeneration(&secondCd, &firstCd);
          __Render_ResetCells(render->firstGenArena, &firstCd);
        }
      }
      deltaTime = 0;
      GeneratorGOL2D_IncrementGen();
    }

    deltaTime += GetFrameTime();

    Cells2D actualCd = CURRENT_GENERATION % 2 == 0 ? firstCd : secondCd;

    // TODO: This should be drawn in a single call
    for (int i = 0; i < CELL_COUNT; i++) {
      if (actualCd.cells[i].is_alive) {
        DrawRectangle(actualCd.positionsX[i], actualCd.positionsY[i],
                      CELL_HEIGHT_RATIO, CELL_WIDTH_RATIO, *actualCd.colors[i]);
      }
    }

    Menu_Draw(&menu);
    EndDrawing();

    // free objects after each frame
    Arena_Free(render->frameArena);

    // TODO: Check, if the mode changed, then free the modeArena
  }

  // teardown the objects after the window has been closed
  Arena_Free(render->firstGenArena);
  Arena_Free(render->secondGenArena);
}

void __Render_ResetCells(Arena *arena, Cells2D *c2d) {
  // Arena_Free(arena);
  // Cells2D_InitArraysBasedOnCellSize(arena, c2d);
}