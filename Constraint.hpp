#pragma once

#include "Particle.hpp"
#include <cmath>
#include <memory>
#include <vector>

class Constraint {
public:
  Constraint(std::shared_ptr<PhysicsObject> particle, Vector2f position);
  void C2();

private:
  std::shared_ptr<PhysicsObject> particle;
  Vector2f position;
};
