#ifndef RENDER_H
#define RENDER_H

#include "dstructs/arena.h"
#include "cellular/cells.h"

typedef enum RenderMode {
  RENDER_MODE_INIT,
  RENDER_MODE_2D,
  RENDER_MODE_3D,
  MAX_RENDER_MODE
} RenderMode;

typedef struct Render {
  Arena *modeArena;
  Arena *firstGenArena;
  Arena *secondGenArena;
  Arena *frameArena;
  RenderMode currentMode;
} Render;

void Render_Window(Render *render);

void __Render_ResetCells(Arena *arena, Cells2D *c2d);
#endif