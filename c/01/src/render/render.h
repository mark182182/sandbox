#ifndef RENDER_H
#define RENDER_H

#include "dstructs/arena.h"
#include "cellular/cells.h"

extern float render2DSpeed;

typedef enum RenderMode {
  RENDER_MODE_INIT,
  RENDER_MODE_2D,
  RENDER_MODE_3D,
  MAX_RENDER_MODE
} RenderMode;

typedef struct Render {
  Arena *mode2DArena;
  Arena *mode3DArena;
  Arena *frame2DArena;
  Arena *frame3DArena;
  RenderMode currentMode;
} Render;

void Render_Window(Render *render);

#endif