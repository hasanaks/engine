#include <iostream>
#include <raylib.h>

#include "World.hpp"

int main() {
  SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(1200, 800, "Engine");

  Camera2D camera = {
      .offset{GetScreenWidth() / 2.f, GetScreenHeight() / 2.f},
      .target{},
      .rotation{},
      .zoom = 1,
  };

  World world;
  auto particle = std::make_shared<Particle>();
  particle->mass = 100;
  world.AddParticle(particle);

  float accumulator = 0;
  float physicsTimeStep = 0.01f;

  while (!WindowShouldClose()) {
    accumulator += GetFrameTime();

    if (IsKeyDown(KEY_LEFT)) {
      camera.target.x -= 10;
    }

    if (IsKeyDown(KEY_RIGHT)) {
      camera.target.x += 10;
    }

    if (IsKeyDown(KEY_UP)) {
      camera.target.y -= 10;
    }

    if (IsKeyDown(KEY_DOWN)) {
      camera.target.y += 10;
    }

    while (accumulator >= physicsTimeStep) {
      world.Step(physicsTimeStep);
	  accumulator -= physicsTimeStep;
    }

    BeginDrawing();

    ClearBackground(BLACK);

    BeginMode2D(camera);
    DrawRectangle(particle->position.x, -particle->position.y, 60, 60, WHITE);
    BeginMode2D(camera);

    EndDrawing();
  }

  CloseWindow();
}
