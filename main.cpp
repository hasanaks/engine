#include <iostream>
#include <raylib.h>

#include "World.hpp"

int main() {
  InitWindow(1200, 800, "Engine");

  SetTargetFPS(120);

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

  while (!WindowShouldClose()) {
    world.Step(GetFrameTime());

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

    BeginDrawing();

    ClearBackground(BLACK);

	BeginMode2D(camera);
    DrawRectangle(particle->position.x, -particle->position.y, 60, 60, WHITE);
	BeginMode2D(camera);

    EndDrawing();
  }

  CloseWindow();
}
