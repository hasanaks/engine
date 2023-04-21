#pragma once

#include "Particle.hpp"
#include <cmath>
#include <memory>
#include <vector>

class ImpulseSolver {

public:
  ImpulseSolver(std::shared_ptr<PhysicsObject> particle1, std::shared_ptr<PhysicsObject> particle2);
  void Imp();

private:
  std::shared_ptr<PhysicsObject> particle1;
  std::shared_ptr<PhysicsObject> particle2;
};
