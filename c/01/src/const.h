#ifndef CONST_H
#define CONST_H

#include <raylib.h>

typedef struct Const {
  // TODO: These should come from a config file
  const int SCREEN_WIDTH;
  const int SCREEN_HEIGHT;
  const Color RANDOM_COLORS[24];
} Const;

const Const DEFAULT_CONST = {
    .SCREEN_WIDTH = 1280,
    .SCREEN_HEIGHT = 720,
    .RANDOM_COLORS = {LIGHTGRAY, GRAY,  DARKGRAY, YELLOW, GOLD,   ORANGE,
                      PINK,      RED,   MAROON,   GREEN,  LIME,   DARKGREEN,
                      SKYBLUE,   BLUE,  DARKBLUE, PURPLE, VIOLET, DARKPURPLE,
                      BEIGE,     BROWN, DARKBROWN}};

#endif