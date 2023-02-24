#pragma once

#include "Particle.hpp"
#include "Vector.hpp"
#include <algorithm>
#include <memory>
#include <vector>

class World {
public:
  void Step(float dt);
  void AddParticle(std::shared_ptr<Particle> particle);
  void RemoveParticle(std::shared_ptr<Particle> particle);

private:
  std::vector<std::shared_ptr<Particle>> particles;
  const Vector2 gravity = {0, -10};
};
