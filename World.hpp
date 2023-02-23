#pragma once

#include <algorithm>
#include <memory>
#include <vector>
#include "Vector.hpp"
#include "Particle.hpp"

class World {
public:
  void Step(float dt) {
	for (auto& particle : particles) {
	  particle->force += particle->mass * gravity;

	  particle->position += particle->velocity * dt + 0.5f * particle->velocity * dt * dt;
	  particle->velocity += particle->force / particle->mass * dt;

	  particle->force = {0, 0};
	}
  }

  void AddParticle(std::shared_ptr<Particle> particle) {
	particles.push_back(particle);
  }

  void RemoveParticle(std::shared_ptr<Particle> particle) {
	particles.erase(std::remove(particles.begin(), particles.end(), particle), particles.end());
  }

private:
  std::vector<std::shared_ptr<Particle>> particles;
  const Vector2 gravity = {0, -10};
};
