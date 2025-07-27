#ifndef RENDERER_H
#define RENDERER_H

#include "arena.h"

typedef enum RenderMode {
  RENDER_MODE_INIT,
  RENDER_MODE_2D,
  RENDER_MODE_3D,
  MAX_RENDER_MODE
} RenderMode;

typedef struct Render {
  // cleared at every mode's end; e.g 2D or 3D
  Arena *modeArena;
  // cleared at every frame
  Arena *frameArena;

  RenderMode currentMode;

} Render;

void Render_Window(Render *renderer);
void Render_TeardownAfterWindow(Render *renderer);

#endif