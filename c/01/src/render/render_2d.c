#include "render_2d.h"
#include "render.h"
#include "font.h"
#include "cellular/gen_gol2d.h"

#include <assert.h>
#include <raylib.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include "const.h"
#include "cellular/cells.h"
#include "menu.h"
#include <time.h>

Render2D Render2D_Init() {
  Render2D render2d = {
      .render2DSpeed = 0.2f, .firstC2d = {0}, .secondC2d = {0}};
  return render2d;
}

void Render2D_RenderMode(Render2D *render2d, Render *render) {
  // initialize everything once
  if (CURRENT_GENERATION == 0) {
    Cells2D firstC2d = render2d->firstC2d;
    Cells2D secondC2d = render2d->secondC2d;

    Cells2D_InitArraysBasedOnCellSize(render->mode2DArena, &firstC2d);
    Cells2D_InitArraysBasedOnCellSize(render->mode2DArena, &secondC2d);

    GeneratorGOL2D_InitializeCells(&firstC2d, true);
    GeneratorGOL2D_InitializeCells(&secondC2d, false);
  }



  Menu_Update(&render->menu);

  // would implement batched rendering, draw calls here, if needed

  // TODO: These should come from the 2D menu
  /*
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
  */

  if (render->isPaused == 0 && render->deltaTime >= render2d->render2DSpeed) {
    clock_t time = clock();
    if (CURRENT_GENERATION != 0) {
      // TODO: The display is weird, somehow the display of the cells doesn't
      // match up with the state
      if (CURRENT_GENERATION % 2 == 0) {
        GeneratorGOL2D_NextGeneration(&render2d->firstC2d,
                                      &render2d->secondC2d);
      } else {
        GeneratorGOL2D_NextGeneration(&render2d->secondC2d,
                                      &render2d->firstC2d);
      }
    } else {
      CURRENT_GENERATION++;
    }
    render->deltaTime = 0;
  }
  render->deltaTime += GetFrameTime();

  Cells2D actualCd =
      CURRENT_GENERATION % 2 == 0 ? render2d->secondC2d : render2d->firstC2d;

  // TODO: This should be drawn in a single call
  for (int i = 0; i < CELL_COUNT; i++) {
    if (actualCd.cells[i].is_alive) {
      DrawRectangle(actualCd.positionsX[i], actualCd.positionsY[i],
                    CELL_HEIGHT_RATIO, CELL_WIDTH_RATIO, *actualCd.colors[i]);
    }
  }

  // free objects after each frame
  Arena_Free(render->frame2DArena);

  // TODO: Check, if the mode changed, then free the modeArena
}