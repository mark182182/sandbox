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

// TODO: Rewrite this in C
void Render_Window(Render *render) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "CA Renderer");

  // load any long living resources here
  // Menu menu = {0};
  // Menu_Init();

  bool isWireframeMode = false;
  int pressed = 0;
  bool isPaused = false;
  float renderSpeed = 0.2f;
  float deltaTime = 0;
  int fpsCap = 60;
  SetTargetFPS(fpsCap);

  Cells2D firstCd = {0};
  Cells2D secondCd = {0};

  Cells2D_InitArraysBasedOnCellSize(render->firstGenArena, &firstCd);
  Cells2D_InitArraysBasedOnCellSize(render->secondGenarena, &secondCd);

  GeneratorGOL2D_InitializeCells(&firstCd);
  GeneratorGOL2D_InitializeCells(&secondCd);

  while (!WindowShouldClose() && pressed != 'q') {
    ClearBackground(WHITE);

    // update variables here
    // Menu_Update();

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
      Arena_Free(render->firstGenArena);
      Arena_Free(render->secondGenarena);

      GeneratorGOL2D_InitializeCells(render->firstGenArena);

      CURRENT_GENERATION = 0;
    }

    if (pressed == 'p') {
      isPaused = !isPaused;
    }

    if (pressed == 'w') {
      renderSpeed -= 0.1f;
    }

    if (pressed == 's') {
      renderSpeed += 0.1f;
    }

    if (isPaused == 0 && deltaTime >= renderSpeed) {
      clock_t time = clock();
      if (CURRENT_GENERATION % 2 == 0) {
        GeneratorGOL2D_NextGeneration(&secondCd, &firstCd);
        Arena_Free(&firstCd);
      } else {
        GeneratorGOL2D_NextGeneration(&firstCd, &secondCd);
        Arena_Free(&secondCd);
      }
      deltaTime = 0;
    }
    deltaTime += GetFrameTime();

    Cells2D actualCd = CURRENT_GENERATION % 2 == 0 ? firstCd : secondCd;

    for (int i = 0; i < CELL_COUNT; i++) {
      assert(&actualCd != NULL);
      if (actualCd.cells[i].is_alive) {
        DrawRectangle(actualCd.positionsX[i], actualCd.positionsY[i],
                      CELL_HEIGHT_RATIO, CELL_WIDTH_RATIO,
                      // TODO: THIS LINE IS CAUSING SEGFAULTS!
                      *actualCd.colors[i]);
        // TODO: THIS LINE IS CAUSING SEGFAULTS!
      }
    }

    Menu_Draw();
    EndDrawing();

    // free objects after each frame
    // TODO: fix this once arena allocator is implemented

    // Arena_Free(render->frameArena);

    // TODO: Check, if the mode changed, then free the modeArena
  }

  // teardown the objects after the window has been closed
}