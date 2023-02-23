#include <iostream>
#include <raylib.h>

#include "World.hpp"

int main() {
  InitWindow(800, 600, "Engine");

  SetTargetFPS(60);

  World world;
  auto particle = std::make_shared<Particle>();
  particle->mass = 100;
  world.AddParticle(particle);

  while (!WindowShouldClose()) {
	world.Step(GetFrameTime());

    BeginDrawing();

    ClearBackground(BLACK);
    DrawRectangle(particle->position.x, -particle->position.y, 60, 60, WHITE);
     
    EndDrawing();
  }

  CloseWindow();
}
