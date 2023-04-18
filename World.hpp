#pragma once

#include "Particle.hpp"
#include "Collision.hpp"
#include "Constraint.hpp"
#include <algorithm>
#include <memory>
#include <vector>

class World {
public:
  World(Vector2f gravity);
  void Step(float dt);
  void AddParticle(std::shared_ptr<Particle> particle);
  void RemoveParticle(std::shared_ptr<Particle> particle);
  std::vector<Particle> CopyState();
  void BuildBox(std::shared_ptr<Particle> pickle);
  Vector2f gravity{0};

private:
  std::vector<std::shared_ptr<Particle>> particles;
};
