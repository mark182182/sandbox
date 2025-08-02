#ifndef RENDER_2D
#define RENDER_2D

#include "render.h"

typedef struct Render2D {
  // TODO: include the relevant fields
  float render2DSpeed;
  Cells2D firstC2d;
  Cells2D secondC2d;
} Render2D;

Render2D Render2D_Init();
void Render2D_RenderMode(Render2D *render2d, Render *render);

#endif