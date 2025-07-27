#include "render.h"
#include "font.h"
#include "gen_gol2d.h"

#include <assert.h>
#include <raylib.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include "str.h"
#include "const.h"
#include "menu.h"

/* TODO: Rewrite this in C
void Render_Window(Render *renderer) {
  InitWindow(DEFAULT_CONST.SCREEN_WIDTH, DEFAULT_CONST.SCREEN_HEIGHT,
             "Graphics example");

  // load any long living resources here
  Menu menu = Menu();
  menu.init();

  bool isWireframeMode = false;
  int pressed = 0;
  bool isPaused = false;
  float renderSpeed = 0.2f;
  float deltaTime = 0;
  int fpsCap = 60;
  SetTargetFPS(fpsCap);

  Gol2dCells2D cd = Gol2dCells2D();

  Gol2dGeneratorInitArraysBasedOnCellSize(&cd);
  GeneratorGOL2D_InitializeCells(&cd);

  // Arena allocator should be used instead
  // std::unique_ptr<Gol2dCells2D> previousCd = nullptr;

  while (!WindowShouldClose() && pressed != 'q') {
    ClearBackground(WHITE);

    // update variables here
    menu.update();

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

    BeginDrawing();

    if (pressed == 'r') {
      GeneratorGOL2D_InitializeCells(&cd);
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
      auto a = clock();
      // before the next generation, we have to make a copy of the first,
      // generation to check the neighbours

      // TODO: instead of doing this, a new arena allocator should be used when
      // the new cells are generated
      // previousCd =
      //     stdunique_ptr<Gol2dCells2D>(Gol2dGeneratordeepCopyCells(&cd));
      // Gol2dGeneratornextGeneration(&cd, previousCd.get());
      deltaTime = 0;
    }
    deltaTime += GetFrameTime();

    for (int i = 0; i < CELL_COUNT; i++) {
      if (cd.cells[i].is_alive) {
        DrawRectangle(cd.positionsX[i], cd.positionsY[i], CELL_HEIGHT_RATIO,
                      CELL_WIDTH_RATIO, *cd.colors[i]);
      }
    }

    Menu_Draw();
    EndDrawing();

    // free objects after each frame
    // TODO: fix this once arena allocator is implemented
    // renderer->frameArena->deallocate();
  }

  // teardown the objects after the window has been closed
  Cells2D_FreeArrays(&cd);
}
*/