#include "Constraint.hpp"

Constraint::Constraint(std::shared_ptr<PhysicsObject> physicsObject,
                       Vector2f position)
    : physicsObject(physicsObject), position(position) {}

void Constraint::C2() {
  auto relativePosition = physicsObject->position - position;
  auto lambda = (-physicsObject->force.dot(relativePosition) -
                 (physicsObject->mass *
                  physicsObject->velocity.dot(physicsObject->velocity))) /
                relativePosition.dot(relativePosition);

  physicsObject->force += (relativePosition)*lambda;
}
