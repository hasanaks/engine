#include "World.hpp"

void World::Step(float dt) {
  for (auto &particle : particles) {
    particle->force += particle->mass * gravity;
    auto acceleration = particle->force / particle->mass;

    particle->position +=
        particle->velocity * dt + 0.5f * acceleration * dt * dt;
    particle->velocity += 0.5f * (particle->acceleration + acceleration) * dt;

    particle->acceleration = acceleration;
    particle->force = {0, 0};
  }
}

void World::AddParticle(std::shared_ptr<Particle> particle) {
  particles.push_back(particle);
}

void World::RemoveParticle(std::shared_ptr<Particle> particle) {
  particles.erase(std::remove(particles.begin(), particles.end(), particle),
                  particles.end());
}

std::vector<Particle> World::CopyState() {
  std::vector<Particle> copied;

  for (auto &particle : particles) {
    copied.push_back(*particle);
  }

  return copied;
}
