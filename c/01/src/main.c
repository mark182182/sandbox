#include "render.h"

int main() {
  // TODO: initialize this properly

  
  Arena frameArena = Arena_Init(&permanentStorage, 1024);

  Render render = {
      .currentMode = RENDER_MODE_INIT,
      .frameArena = frameArena.modeArena = NULL,
      .firstGenArena = NULL,
      .secondGenArena = NULL,
  };

  Render_Window(&render);
  return 0;
}
