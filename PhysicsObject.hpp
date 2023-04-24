#pragma once
#include "Collider.hpp"
#include <optional>

struct PhysicsObject {
  float mass;
  Vector2f position;
  Vector2f velocity;
  Vector2f force;

  std::optional<RectangleCollider> rectangleCollider;
};
