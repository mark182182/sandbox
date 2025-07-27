#include "menu.h"

#include <raylib.h>
#include "str.h"
#include "font.h"
#include <time.h>

void drawTextInMenu(Vector2 firstTextPos, Vector2 *currentTextPos,
                    const char *textToDraw, int fontSize, Color rectColor,
                    Color textColor, void(*onCollision(void))) {
  Color currentRectColor = rectColor;
  Vector2 textLength = MeasureTextEx(selectedFont, textToDraw, fontSize, 0);

  Rectangle textRect =
      Rectangle{firstTextPos.x, currentTextPos->y, textLength.x, textLength.y};

  if (CheckCollisionPointRec(cursorPosition, textRect)) {
    currentRectColor = GRAY;
    onCollision();
  }

  DrawRectangleRec(textRect, currentRectColor);
  DrawTextEx(selectedFont, textToDraw,
             Vector2{firstTextPos.x, currentTextPos->y}, fontSize, 0,
             textColor);

  currentTextPos->x += textLength.x;
  currentTextPos->y += textLength.y;
}

void init() {
  displayFont DisplayFont::loadFonts();
  selectedFont = DisplayFont::getFont(DisplayFont::FiraCodeRetina);
}

void update() { cursorPosition = GetMousePosition(); }

void draw() {
  int fontSize = 32;
  Vector2 firstTextPos = Vector2{10, 40};
  Vector2 longestTextLength = Vector2{0, 0};

  Vector2 currentTextPos = Vector2{firstTextPos.x, firstTextPos.y};

  std::string fpsText = ("FPS: " + std::to_string(GetFPS())).c_str();
  std::string frametimeText =
      "Frametime: " + std::to_string(GetFrameTime()) + " ms";
  std::string wireFrameText = "Wireframe mode";
  std::string quitText = "Quit";

  DrawRectangle(firstTextPos.x, firstTextPos.y, currentTextPos.x * 4,
                currentTextPos.y * 4, RAYWHITE);

  drawTextInMenu(firstTextPos, &currentTextPos, fpsText.c_str(), fontSize,
                 BLACK, RED, [fpsText]() { printf(fpsText.c_str()); });
  drawTextInMenu(firstTextPos, &currentTextPos, frametimeText.c_str(), fontSize,
                 BLACK, RED, []() {});
  drawTextInMenu(firstTextPos, &currentTextPos, wireFrameText.c_str(), fontSize,
                 BLACK, RED, []() {});
  drawTextInMenu(firstTextPos, &currentTextPos, quitText.c_str(), fontSize,
                 BLACK, RED, []() {});
}

Menu menu = {

}