#include "const.h"
#include "render/render.h"
#include <stdbool.h>
#include "render/menu.h"
#include <stdlib.h>

int main() {
  InitializeConstants();

  // load any long living resources here

  Arena mode2DArena =
      Arena_Init("modeArena", &mode2DArenaStorage, MODE_2D_STORAGE_SIZE);
  Arena mode3DArena =
      Arena_Init("modeArena", &mode3DArenaStorage, MODE_3D_STORAGE_SIZE);

  Arena frame2DArena =
      Arena_Init("frame2DArena", &frame2DArenaStorage, FRAME_2D_STORAGE_SIZE);
  Arena frame3DArena =
      Arena_Init("frame3DArena", &frame3DArenaStorage, FRAME_3D_STORAGE_SIZE);

  Render render = {.mode2DArena = &mode2DArena,
                   .mode3DArena = &mode3DArena,
                   .frame2DArena = &frame2DArena,
                   .frame3DArena = &frame3DArena,

                   .menu = NULL,

                   .isWireframeMode = false,
                   .keyPressed = 0,
                   .isPaused = false,
                   .deltaTime = 0,
                   .fpsCap = FPS_CAP};

  Render_RenderWindow(&render);
  return 0;
}
