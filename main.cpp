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
	const float frameTime = GetFrameTime();

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

    std::vector<Particle> lastState = world.CopyState();

    accumulator += frameTime;
    while (accumulator >= physicsTimeStep) {
	  if (accumulator - physicsTimeStep < physicsTimeStep) {
		lastState = world.CopyState();
	  }

      world.Step(physicsTimeStep);
      accumulator -= physicsTimeStep;
    }

    const auto interpolation = accumulator / physicsTimeStep;

    auto currentState = world.CopyState();
    std::vector<Vector2f> positions;
    std::transform(currentState.cbegin(), currentState.cend(),
                   lastState.cbegin(), std::back_inserter(positions),
                   [&interpolation](const auto& p1, const auto& p2) {
                     return p1.position * interpolation +
                            p2.position * (1.f - interpolation);
                   });

    BeginDrawing();

    ClearBackground(BLACK);

    BeginMode2D(camera);
    for (auto &position : positions) {
      DrawRectangle(position.x, -position.y, 60, 60, WHITE);
    }
    EndMode2D();

    EndDrawing();
  }

  CloseWindow();
}
