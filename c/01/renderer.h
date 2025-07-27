#ifndef RENDERER_H
#define RENDERER_H

#include "arena.h"

typedef enum RenderMode {
  RENDER_MODE_2D,
  RENDER_MODE_3D,
  MAX_RENDER_MODE
} RenderMode;

typedef struct Renderer {

  // the lifetime of this arena is the lifetime of the renderer/application
  Arena *permanentArena;
  // cleared at every mode's end; e.g 2D or 3D
  Arena *modeArena;
  // cleared at every frame
  Arena *frameArena;

  RenderMode currentMode;

} Renderer;

void Renderer_Render(Renderer *renderer);

#endif