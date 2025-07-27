#ifndef CONST_H
#define CONST_H

#include <raylib.h>
#include "arena.h"

// the lifetime of this arena is the lifetime of the renderer/application
Arena *permanentArena;

/*
TODO: If the below values should come from a configuration, a temporary arena
would need to be used an cleared whenever the configuration is reloaded. This
means that any downstream usage, e.g. window initialization would need to be
re-run as well.
*/

typedef enum RenderConst {
  SCREEN_WIDTH = 1024,
  SCREEN_HEIGHT = 720,
} RenderConst;

extern const Color RANDOM_COLORS[24];

#endif