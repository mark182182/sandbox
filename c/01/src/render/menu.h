#ifndef MENU_H
#define MENU_H

#include <raylib.h>

typedef enum RenderMode {
  RENDER_MODE_INIT,
  RENDER_MODE_2D,
  RENDER_MODE_3D,
  MAX_RENDER_MODE
} RenderMode;

/**
 * The main menu that is used to select the render modes. Also contains the main
 * read-only settings for other menus, like the selected font or the cursor
 * position.
 */
typedef struct Menu {
  Font selectedFont;
  Vector2 cursorPosition;

  // TODO: A state machine to handle the mode changes would be better, but this keeps it simple for now
  RenderMode prevMode;
  RenderMode currentMode;
} Menu;

Menu Menu_Init();
void Menu_Update(Menu *menu);
void Menu_Draw(Menu *menu);

void __DrawTextInMenu(Menu *menu, Vector2 firstTextPos, Vector2 *currentTextPos,
                      const char *textToDraw, int fontSize, Color rectColor,
                      Color textColor, void (*onCollisionFn)(void));

#endif