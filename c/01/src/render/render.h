#ifndef RENDER_H
#define RENDER_H

#include "menu.h"
#include "dstructs/arena.h"
#include "cellular/cells.h"

/**
 * The main render window that contains the render loop, where the the main
 * menu gets drawn. Also used for selecting the other render modes via the menu.
 */
typedef struct Render {
  Arena *mode2DArena;
  Arena *mode3DArena;
  Arena *frame2DArena;
  Arena *frame3DArena;

  Menu *menu;

  bool isWireframeMode;
  // NOTE: might be worth replacing this to a ring buffer
  int keyPressed;
  bool isPaused;
  float deltaTime;
  int fpsCap;

} Render;

void Render_RenderWindow(Render *render);

#endif