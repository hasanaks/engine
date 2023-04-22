#pragma once

#include "PhysicsObject.hpp"
#include <cmath>
#include <memory>
#include <vector>

class ImpulseSolver {

public:
  ImpulseSolver(PhysicsObject *physicsObject1, PhysicsObject *physicsObject2);
  void Imp();

private:
  PhysicsObject *physicsObject1;
  PhysicsObject *physicsObject2;
};
