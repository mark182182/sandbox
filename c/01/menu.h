#ifndef MENU_H
#define MENU_H

#include <raylib.h>

typedef struct Menu {
  Font selectedFont;
  Vector2 cursorPosition;
} Menu;

void Menu_Init();
void Menu_Update();
void Menu_Draw();

#endif