#pragma once

#include "Particle.hpp"
#include <cmath>
#include <memory>
#include <vector>

class Constraint {
public:
  Constraint(std::shared_ptr<Particle> A, Vector2f pos);
  void C2();

private:
  Vector2f *positionA{};
  Vector2f positionB{};
  Vector2f *Va{};
  Vector2f *Vb{};
  Vector2f relP{};
  Vector2f *forcext{};
  float m;
  float lambda{};
  Vector2f forceC{};
  std::shared_ptr<Particle> ret{};
};
