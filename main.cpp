#include <iostream>
#include <raylib.h>
#include <rlgl.h>

#include "Eigen/Dense"

#include "World.hpp"

int main() {
  SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(1200, 800, "Engine");

  Camera2D camera{};
  camera.zoom = 1;

  World world({0, 10.f});

  float accumulator = 0;
  float physicsTimeStep = 0.01f;

  while (!WindowShouldClose()) {
    const float frameTime = GetFrameTime();

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      Vector2 delta = GetMouseDelta();
      Vector2f deltaf = {delta.x, delta.y};
      deltaf *= -1.0f / camera.zoom;

      camera.target.x += deltaf.x();
      camera.target.y += deltaf.y();
    }

    float wheel = GetMouseWheelMove();
    if (wheel != 0) {
      camera.target = GetScreenToWorld2D(GetMousePosition(), camera);
      camera.offset = GetMousePosition();

      const float zoomIncrement = 0.125f;
      camera.zoom += wheel * zoomIncrement * camera.zoom;
      if (camera.zoom < zoomIncrement)
        camera.zoom = zoomIncrement;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
      auto physicsObject = std::make_shared<PhysicsObject>();
      physicsObject->mass = 1;

      auto pos = GetScreenToWorld2D(GetMousePosition(), camera);
      physicsObject->position = Vector2f{pos.x, pos.y};
      physicsObject->collider = Collider{Vector2f{60.0f, 60.0f}};

      world.AddParticle(physicsObject);
    }

    accumulator += frameTime;

    std::vector<PhysicsObject> lastState;
    if (accumulator < physicsTimeStep) {
      lastState = world.CopyState();
    }

    while (accumulator >= physicsTimeStep) {
      if (accumulator - physicsTimeStep < physicsTimeStep) {
        lastState = world.CopyState();
      }

      world.Step(physicsTimeStep);
      accumulator -= physicsTimeStep;
    }

    const auto interpolation = accumulator / physicsTimeStep;

    auto currentState = world.CopyState();
    std::vector<PhysicsObject> interpolatedState(currentState.size());

    std::transform(currentState.cbegin(), currentState.cend(),
                   lastState.cbegin(), interpolatedState.begin(),
                   [interpolation](const auto &p1, const auto &p2) {
                     auto a = p2;
                     a.position = p1.position * (1 - interpolation) +
                                  p2.position * interpolation;
                     return a;
                   });

    BeginDrawing();

    ClearBackground(BLACK);

    BeginMode2D(camera);

    for (const auto &object : interpolatedState) {
      if (!object.collider.has_value())
        continue;

      const auto &collider = object.collider.value();
      DrawRectangle(object.position.x(), object.position.y(),
                    collider.dimensions.x(), collider.dimensions.y(), WHITE);
    }

    EndMode2D();

    DrawFPS(0, 0);

    EndDrawing();
  }

  CloseWindow();
}
