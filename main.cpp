#include <iostream>
#include <raylib.h>

int main() {
  InitWindow(120, 180, "Engine");

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawRectangle(0, 0, 100, 100, BLUE);
     
    EndDrawing();
  }

  CloseWindow();
}
