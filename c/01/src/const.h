#ifndef CONST_H
#define CONST_H

#include <raylib.h>
#include "dstructs/arena.h"

/*
TODO: If the below values should come from a configuration, a temporary arena
would need to be used an cleared whenever the configuration is reloaded. This
means that any downstream usage, e.g. window initialization would need to be
re-run as well.
*/

extern bool DEBUG_MODE;

// since it doesn't add any benefit to declare typedefs for the enums, it's best
// to omit it (would only be useable in some cases, e.g. when the a specified
// value has to be passed of the given enum type to state the intent)

enum { SCREEN_WIDTH = 1280, SCREEN_HEIGHT = 720, FPS_CAP = 60 };

extern const Color RANDOM_COLORS[24];

/**
 *  The lifetime of this arena is the lifetime of the renderer/application
 */
extern Arena permanentArena;

// any constant expression that cannot be initialized at compile time
void InitializeConstants();

#endif