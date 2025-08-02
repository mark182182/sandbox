#include "render.h"
#include "font.h"
#include "cellular/gen_gol2d.h"

#include "dstructs/arena.h"
#include <assert.h>
#include <raylib.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include "const.h"
#include "menu.h"
#include <time.h>
#include <stdbool.h>
#include "render_2d.h"

void Render_RenderWindow(Render *render) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "CA Renderer");
  // must be called after InitWindow
  Menu menu = Menu_Init();

  render->menu = &menu;

  SetTargetFPS(render->fpsCap);

  bool isFirstFrame = true;
  while (!WindowShouldClose()) {
    render->keyPressed = GetCharPressed();

    if (render->fpsCap == 60 && render->keyPressed == 'c') {
      render->fpsCap = 0;
      SetTargetFPS(render->fpsCap);
    } else if (render->fpsCap == 0 && render->keyPressed == 'c') {
      render->fpsCap = 60;
      SetTargetFPS(render->fpsCap);
    }

    if (!render->isWireframeMode && render->keyPressed == 't') {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      render->isWireframeMode = true;
    } else if (render->isWireframeMode && render->keyPressed == 't') {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      render->isWireframeMode = false;
    }

    if (menu.currentMode != menu.prevMode) {
      Arena_FreeZeroed(render->mode2DArena);
      Arena_FreeZeroed(render->mode3DArena);
    }

    // update variables here
    ClearBackground(WHITE);

    BeginDrawing();

    // select the current mode
    // TODO: implement the switching on modes in the main menu
    switch (menu.currentMode) {
    case RENDER_MODE_INIT:
      break;
    case RENDER_MODE_2D:
      if (isFirstFrame) {
        Render2D render2d = Render2D_Init();
        Render2D_RenderMode(&render2d, render);
      }
      break;
    case RENDER_MODE_3D:
      if (isFirstFrame) {
        // TODO: implement this
        /*
        Render3D render3D = Render3D_Init();
        Render3D_RenderMode(render);
        */
      }
      break;
    default:
      break;
    }

    if (isFirstFrame) {
      isFirstFrame = false;
    }

    Menu_Draw(&menu);

    EndDrawing();
  }

  // teardown the objects after the window has been closed
  Arena_Free(render->mode2DArena);
}
