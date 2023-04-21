#pragma once

#include "PhysicsObject.hpp"
#include <cmath>
#include <memory>
#include <vector>

class ImpulseSolver {

public:
  ImpulseSolver(std::shared_ptr<PhysicsObject> physicsObject1, std::shared_ptr<PhysicsObject> physicsObject2);
  void Imp();

private:
  std::shared_ptr<PhysicsObject> physicsObject1;
  std::shared_ptr<PhysicsObject> physicsObject2;
};
