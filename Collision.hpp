#pragma once

#include "PhysicsObject.hpp"
#include <vector>

struct AABB {
  PhysicsObject *id;
  Vector2f min;
  Vector2f max;

  AABB() = default;
  explicit AABB(PhysicsObject *physicsObject);

  bool OverlappingWith(const AABB &anotherBox) const;
};

std::vector<std::pair<AABB, AABB>>
FindOverlappingBoxes(std::vector<AABB> boxes);
