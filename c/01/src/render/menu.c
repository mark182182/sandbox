#include "menu.h"

#include <raylib.h>
#include "font.h"
#include <time.h>

// TODO: Rewrite this file in C

void Menu_Init() {
  // displayFont DisplayFont::loadFonts();
  // selectedFont = DisplayFont::getFont(DisplayFont::FiraCodeRetina);
}

void Menu_Update() {
  // cursorPosition = GetMousePosition();
}

void Menu_Draw() {
  // int fontSize = 32;
  // Vector2 firstTextPos = Vector2{10, 40};
  // Vector2 longestTextLength = Vector2{0, 0};

  // Vector2 currentTextPos = Vector2{firstTextPos.x, firstTextPos.y};

  // std::string fpsText = ("FPS: " + std::to_string(GetFPS())).c_str();
  // std::string frametimeText =
  //     "Frametime: " + std::to_string(GetFrameTime()) + " ms";
  // std::string wireFrameText = "Wireframe mode";
  // std::string quitText = "Quit";

  // DrawRectangle(firstTextPos.x, firstTextPos.y, currentTextPos.x * 4,
  //               currentTextPos.y * 4, RAYWHITE);

  // __DrawTextInMenu(firstTextPos, &currentTextPos, fpsText.c_str(), fontSize,
  //                BLACK, RED, [fpsText]() { printf(fpsText.c_str()); });
  // __DrawTextInMenu(firstTextPos, &currentTextPos, frametimeText.c_str(),
  // fontSize,
  //                BLACK, RED, []() {});
  // __DrawTextInMenu(firstTextPos, &currentTextPos, wireFrameText.c_str(),
  // fontSize,
  //                BLACK, RED, []() {});
  // __DrawTextInMenu(firstTextPos, &currentTextPos, quitText.c_str(), fontSize,
  //                BLACK, RED, []() {});
}

void __DrawTextInMenu(Vector2 firstTextPos, Vector2 *currentTextPos,
                      const char *textToDraw, int fontSize, Color rectColor,
                      Color textColor, void(*onCollision(void))) {
  // Color currentRectColor = rectColor;
  // Vector2 textLength = MeasureTextEx(selectedFont, textToDraw, fontSize, 0);

  // Rectangle textRect =
  //     Rectangle{firstTextPos.x, currentTextPos->y, textLength.x,
  //     textLength.y};

  // if (CheckCollisionPointRec(cursorPosition, textRect)) {
  //   currentRectColor = GRAY;
  //   onCollision();
  // }

  // DrawRectangleRec(textRect, currentRectColor);
  // DrawTextEx(selectedFont, textToDraw,
  //            Vector2{firstTextPos.x, currentTextPos->y}, fontSize, 0,
  //            textColor);

  // currentTextPos->x += textLength.x;
  // currentTextPos->y += textLength.y;
}