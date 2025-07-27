#include <raylib.h>

void can_switch_windows_in_different_modes() {
  InitWindow(640, 480, "raylib_example");

  while (!WindowShouldClose()) {
    ClearBackground(WHITE);

    BeginDrawing();

    Vector2 vecUp = {.x = 600, .y = 600};
    Vector2 vecLeft = {.x = 200, .y = 200};
    Vector2 vecRight = {.x = 800, .y = 200};

    DrawTriangle(vecUp, vecLeft, vecRight, BLACK);

    EndDrawing();
  }

  CloseWindow();
}

int main() {
  can_switch_windows_in_different_modes();
  // TODO: add more calls, as needed
}