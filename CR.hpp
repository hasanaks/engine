#pragma once

#include "Particle.hpp"
#include <cmath>
#include <memory>
#include <vector>

class ImpulseSolver {

public:
  ImpulseSolver(std::shared_ptr<Particle> P1, std::shared_ptr<Particle> P2);
  Vector2f normalFinder();
  void Imp();

private:
  std::shared_ptr<Particle> A;
  std::shared_ptr<Particle> B;
};