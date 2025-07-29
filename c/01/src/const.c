#include "const.h"

// bool DEBUG_MODE = false;

const Color RANDOM_COLORS[24] = {
    LIGHTGRAY, GRAY,   DARKGRAY, YELLOW,     GOLD,      ORANGE,  PINK,
    RED,       MAROON, GREEN,    LIME,       DARKGREEN, SKYBLUE, BLUE,
    DARKBLUE,  PURPLE, VIOLET,   DARKPURPLE, BEIGE,     BROWN,   DARKBROWN};

Arena permanentArena;

void InitializeConstants() {
  permanentArena =
      Arena_Init("permanentArena", &permanentStorage, PERMANENT_STORAGE_SIZE);
}