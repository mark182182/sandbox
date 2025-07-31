#include "menu.h"

#include <raylib.h>
#include "font.h"
#include <time.h>
#include <stdlib.h>
#include "common.h"
#include <string.h>

Menu Menu_Init() {
  LoadFonts();
  Font font = fonts_by_type[FONT_TYPE_FIRA_CODE_RETINA];
  Menu menu = {.selectedFont = font, .cursorPosition = {.x = 0, .y = 0}};
  return menu;
}

void Menu_Update(Menu *menu) { menu->cursorPosition = GetMousePosition(); }

void Menu_Draw(Menu *menu) {
  int fontSize = 32;
  Vector2 firstTextPos = {.x = 10, .y = 40};
  Vector2 longestTextLength = {.x = 0, .y = 0};

  Vector2 currentTextPos = {.x = firstTextPos.x, .y = firstTextPos.y};

  char fpsBuffer[128];
  int fpsBase = 10; // decimal base
  char *fpsText = itoa(GetFPS(), fpsBuffer, fpsBase);

  int dec;
  int sign;
  char *frameTime = ecvt(GetFrameTime(), fpsBase, &dec, &sign);
  char frameTimeBuffer[64];

  char decBuffer[8];
  char *decText = itoa(dec, decBuffer, fpsBase);

  strcpy(frameTimeBuffer, decText);
  //strcpy(frameTimeBuffer, frameTime);

  char *frametimeText = frameTimeBuffer;
  char *wireFrameText = "Wireframe mode";
  char *quitText = "Quit";

  DrawRectangle(firstTextPos.x, firstTextPos.y, currentTextPos.x * 4,
                currentTextPos.y * 4, RAYWHITE);

  __DrawTextInMenu(menu, firstTextPos, &currentTextPos, fpsText, fontSize,
                   BLACK, RED, noOp);
  __DrawTextInMenu(menu, firstTextPos, &currentTextPos, frametimeText, fontSize,
                   BLACK, RED, noOp);
  __DrawTextInMenu(menu, firstTextPos, &currentTextPos, wireFrameText, fontSize,
                   BLACK, RED, noOp);
  __DrawTextInMenu(menu, firstTextPos, &currentTextPos, quitText, fontSize,
                   BLACK, RED, noOp);
}

void __DrawTextInMenu(Menu *menu, Vector2 firstTextPos, Vector2 *currentTextPos,
                      const char *textToDraw, int fontSize, Color rectColor,
                      Color textColor, void (*onCollisionFn)(void)) {
  Color currentRectColor = rectColor;
  // TODO: For some reason the font's length is 0
  // Works with the default font
  Vector2 textLength =
      MeasureTextEx(menu->selectedFont, textToDraw, fontSize, 0);

  Rectangle textRect = {.x = firstTextPos.x,
                        .y = currentTextPos->y,
                        .width = textLength.x,
                        .height = textLength.y};

  if (CheckCollisionPointRec(menu->cursorPosition, textRect)) {
    currentRectColor = GRAY;
    // TODO: onCollisionFn();
  }

  DrawRectangleRec(textRect, currentRectColor);
  Vector2 position = {.x = firstTextPos.x, .y = currentTextPos->y};
  DrawTextEx(menu->selectedFont, textToDraw, position, fontSize, 0, textColor);

  currentTextPos->x += textLength.x;
  currentTextPos->y += textLength.y;
}