#ifndef MENU_H
#define MENU_H

#include <raylib.h>

typedef struct Menu {
  Font selectedFont;
  Vector2 cursorPosition;
} Menu;

Menu Menu_Init();
void Menu_Update(Menu *menu);
void Menu_Draw(Menu *menu);

void __DrawTextInMenu(Menu *menu, Vector2 firstTextPos, Vector2 *currentTextPos,
                      const char *textToDraw, int fontSize, Color rectColor,
                      Color textColor, void (*onCollisionFn)(void));

#endif