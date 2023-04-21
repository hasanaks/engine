#include "Constraint.hpp"

Constraint::Constraint(std::shared_ptr<Particle> particle, Vector2f position)
    : particle(particle), position(position) {}

void Constraint::C2() {
  auto relativePosition = particle->position - position;
  auto lambda =
      (-particle->force.dot(relativePosition) -
       (particle->mass * particle->velocity.dot(particle->velocity))) /
      relativePosition.dot(relativePosition);

  particle->force += (relativePosition)*lambda;
}
