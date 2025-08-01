#include "const.h"
#include "render/render.h"

int main() {
  InitializeConstants();

  Arena mode2DArena =
      Arena_Init("modeArena", &mode2DArenaStorage, MODE_2D_STORAGE_SIZE);
  Arena mode3DArena =
      Arena_Init("modeArena", &mode3DArenaStorage, MODE_3D_STORAGE_SIZE);

  Arena frame2DArena =
      Arena_Init("frame2DArena", &frame2DArenaStorage, FRAME_2D_STORAGE_SIZE);
  Arena frame3DArena =
      Arena_Init("frame3DArena", &frame3DArenaStorage, FRAME_3D_STORAGE_SIZE);

  Render render = {.currentMode = RENDER_MODE_INIT,
                   .mode2DArena = &mode2DArena,
                   .mode3DArena = &mode3DArena,
                   .frame2DArena = &frame2DArena,
                   .frame3DArena = &frame3DArena};

  Render_Window(&render);
  return 0;
}
