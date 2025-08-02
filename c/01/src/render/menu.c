#include "menu.h"

#include <raylib.h>
#include "font.h"
#include <stdlib.h>
#include "common.h"
#include <string.h>

Menu Menu_Init() {
  LoadFonts();
  Font font = fonts_by_type[FONT_TYPE_FIRA_CODE_RETINA];
  Menu menu = {.selectedFont = font,
               .cursorPosition = {.x = 0, .y = 0},
               .currentMode = RENDER_MODE_INIT};
  return menu;
}

void Menu_Update(Menu *menu) { menu->cursorPosition = GetMousePosition(); }

void Menu_Draw(Menu *menu) {
  int fontSize = 32;
  Vector2 firstTextPos = {.x = 10, .y = 40};
  Vector2 longestTextLength = {.x = 0, .y = 0};

  Vector2 currentTextPos = {.x = firstTextPos.x, .y = firstTextPos.y};

  // TODO: Revise this, only a temp solution
  char fpsText[128] = "FPS: ";
  char fpsBuffer[6];
  int decBase = 10; // decimal base
  itoa(GetFPS(), fpsBuffer, decBase);

  for (int i = 0; i < strlen(fpsBuffer); i++) {
    fpsText[strlen(fpsText)] = fpsBuffer[i];
  }

  int dec;
  int sign;
  char *frameTime = ecvt(GetFrameTime(), decBase, &dec, &sign);
  char frameTimeText[64] = "Frametime: 0.";

  for (int i = 0; i > dec; i--) {
    frameTimeText[strlen(frameTimeText)] = '0';
  }
  for (int i = 0; i < strlen(frameTime); i++) {
    frameTimeText[strlen(frameTimeText)] = frameTime[i];
  }

  char *wireFrameText = "Wireframe mode";
  char *quitText = "Quit";

  DrawRectangle(firstTextPos.x, firstTextPos.y, currentTextPos.x * 4,
                currentTextPos.y * 4, RAYWHITE);

  __DrawTextInMenu(menu, firstTextPos, &currentTextPos, fpsText, fontSize,
                   BLACK, RED, noOp);
  __DrawTextInMenu(menu, firstTextPos, &currentTextPos, frameTimeText, fontSize,
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
  Vector2 textLength =
      MeasureTextEx(menu->selectedFont, textToDraw, fontSize, 0);

  Rectangle textRect = {.x = firstTextPos.x,
                        .y = currentTextPos->y,
                        .width = textLength.x,
                        .height = textLength.y};

  if (CheckCollisionPointRec(menu->cursorPosition, textRect)) {
    currentRectColor = GRAY;
    onCollisionFn();
  }

  DrawRectangleRec(textRect, currentRectColor);
  Vector2 position = {.x = firstTextPos.x, .y = currentTextPos->y};
  DrawTextEx(menu->selectedFont, textToDraw, position, fontSize, 0, textColor);

  currentTextPos->x += textLength.x;
  currentTextPos->y += textLength.y;
}