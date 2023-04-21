#include "World.hpp"

World::World(Vector2f gravity) : gravity(gravity) {}

void World::Step(float dt) {
  Echoes();
  gebouw();
  for (auto &particle : particles) {
    particle->force += particle->mass * gravity;

    auto acceleration = particle->force / particle->mass;
    particle->position +=
        particle->velocity * dt + 0.5f * acceleration * dt * dt;
    particle->velocity += acceleration * dt;

    particle->force = {0, 0};
  }
}

void World::AddParticle(std::shared_ptr<Particle> particle) {
  if (std::find(particles.begin(), particles.end(), particle) ==
      std::end(particles)) {
    particles.push_back(particle);
  }
}

void World::RemoveParticle(std::shared_ptr<Particle> particle) {
  particles.erase(std::remove(particles.begin(), particles.end(), particle),
                  particles.end());
}

void World::setBoxList() {
  std::vector<AABB> l1;
  for (auto &particle : particles) { // shame on a bro. fr
    l1.push_back(BuildBox(particle));
  }
  activeList = relayer(EdgeInit(l1));
  isActive(activeList);
}

void World::Echoes() {
  setBoxList();

  constraints = {};

  for (int i = 0; i < activeList.size(); i++) {
    ImpulseSolver c{activeList[i].b1.id, activeList[i].b2.id};
    constraints.push_back(c);
  }
}

void World::gebouw() {

  for (auto &constraint : constraints) {
    constraint.Imp();
  }
}

AABB World::BuildBox(std::shared_ptr<Particle> pickle) {

  AABB box{};
  box.id = pickle;
  box.min = pickle->position - Vector2f{0, pickle->transform.y()};
  box.max = pickle->position + Vector2f{pickle->transform.x(), 0};
  return box;
}

std::vector<Particle> World::CopyState() {
  std::vector<Particle> copied;

  for (auto &particle : particles) {
    copied.push_back(*particle);
  }

  return copied;
}
