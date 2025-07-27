#include "render.h"

int main() {
  Render render = {
      .currentMode = RENDER_MODE_INIT,
      .frameArena = 0,
      .modeArena = NULL,
  };
  Render *a = NULL;

  Render_Window(&render);
  return 0;
}
