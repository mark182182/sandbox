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

float render2DSpeed = 0.2f;

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

  Cells2D_InitArraysBasedOnCellSize(render->mode2DArena, &firstCd);
  Cells2D_InitArraysBasedOnCellSize(render->mode2DArena, &secondCd);

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

    if (pressed == 'w') {
      render2DSpeed -= 0.001f;
    }

    if (pressed == 's') {
      render2DSpeed += 0.001f;
    }

    if (isPaused == 0 && deltaTime >= render2DSpeed) {
      clock_t time = clock();
      if (CURRENT_GENERATION != 0) {
        if (CURRENT_GENERATION % 2 == 0) {
          GeneratorGOL2D_NextGeneration(&firstCd, &secondCd);
        } else {
          GeneratorGOL2D_NextGeneration(&secondCd, &firstCd);
        }
      } else {
        CURRENT_GENERATION++;
      }
      deltaTime = 0;
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
    Arena_Free(render->frame2DArena);

    // TODO: Check, if the mode changed, then free the modeArena
  }

  // teardown the objects after the window has been closed
  Arena_Free(render->mode2DArena);
}