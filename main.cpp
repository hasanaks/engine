#include <iostream>
#include <raylib.h>

int main() {
  InitWindow(1920, 1080, "Engine");

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawRectangle(0, 0, 100, 100, BLUE);

    EndDrawing();
  }

  CloseWindow();
}
