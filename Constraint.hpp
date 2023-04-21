#pragma once

#include "PhysicsObject.hpp"
#include <cmath>
#include <memory>
#include <vector>

class Constraint {
public:
  Constraint(std::shared_ptr<PhysicsObject> physicsObject, Vector2f position);
  void C2();

private:
  std::shared_ptr<PhysicsObject> physicsObject;
  Vector2f position;
};
