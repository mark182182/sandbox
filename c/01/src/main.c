#include "render.h"

int main() {
  // TODO: initialize this properly
  Render render = {
      .currentMode = RENDER_MODE_INIT,
      .frameArena = 0,
      .modeArena = NULL,
  };

  Render_Window(&render);
  return 0;
}
