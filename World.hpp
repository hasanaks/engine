#pragma once

#include "Particle.hpp"
#include "Vector.hpp"
#include <algorithm>
#include <memory>
#include <vector>

class World {
public:
  void Step(float dt) {
    for (auto &particle : particles) {
      particle->force += particle->mass * gravity;
      auto acceleration = particle->force / particle->mass;

      particle->position +=
          particle->velocity * dt + 0.5f * acceleration * dt * dt;
      particle->velocity += acceleration * dt;

      particle->force = {0, 0};
    }
  }

  void AddParticle(std::shared_ptr<Particle> particle) {
    particles.push_back(particle);
  }

  void RemoveParticle(std::shared_ptr<Particle> particle) {
    particles.erase(std::remove(particles.begin(), particles.end(), particle),
                    particles.end());
  }

private:
  std::vector<std::shared_ptr<Particle>> particles;
  const Vector2 gravity = {0, -10};
};
