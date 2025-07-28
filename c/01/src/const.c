#include "const.h"
#include "dstructs/arena.h"

const Color RANDOM_COLORS[24] = {
    LIGHTGRAY, GRAY,   DARKGRAY, YELLOW,     GOLD,      ORANGE,  PINK,
    RED,       MAROON, GREEN,    LIME,       DARKGREEN, SKYBLUE, BLUE,
    DARKBLUE,  PURPLE, VIOLET,   DARKPURPLE, BEIGE,     BROWN,   DARKBROWN};

const Arena permanentArena = Arena_Init(&permanentStorage, 1024);