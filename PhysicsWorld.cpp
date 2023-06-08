#include "PhysicsWorld.hpp"

PhysicsWorld::PhysicsWorld(Vector2f gravity) : gravity(gravity) {}

void PhysicsWorld::Step(float dt) {
  ResolveCollisions();

  for (const auto &physicsObject : physicsObjects) {
    UpdatePhysicsObject(physicsObject, dt);
  }
}

void PhysicsWorld::AddPhysicsObject(
    const std::shared_ptr<PhysicsObject> &physicsObject) {
  physicsObjects.insert(physicsObject);
}

void PhysicsWorld::RemovePhysicsObject(
    const std::shared_ptr<PhysicsObject> &physicsObject) {
  physicsObjects.erase(physicsObject);
}

std::vector<PhysicsObject> PhysicsWorld::CopyState() {
  std::vector<PhysicsObject> copied(physicsObjects.size());
  std::transform(physicsObjects.cbegin(), physicsObjects.cend(), copied.begin(),
                 [](const auto &physicsObject) { return *physicsObject; });
  return copied;
}

void PhysicsWorld::UpdatePhysicsObject(
    const std::shared_ptr<PhysicsObject> &physicsObject, float dt) {
  physicsObject->force += physicsObject->mass * gravity;

  auto acceleration = physicsObject->force / physicsObject->mass;
  physicsObject->position +=
      physicsObject->velocity * dt + 0.5f * acceleration * dt * dt;
  physicsObject->velocity += acceleration * dt;

  physicsObject->force = {0, 0};
}

void PhysicsWorld::ResolveCollisions() {
  for (const auto &overlappingBox : FindOverlappingBoxes(GetAABBs())) {
    ImpulseSolver(overlappingBox.first.id, overlappingBox.second.id).Apply();
  }
}

std::vector<AABB> PhysicsWorld::GetAABBs() {
  std::vector<AABB> AABBs(physicsObjects.size());
  std::transform(physicsObjects.cbegin(), physicsObjects.cend(), AABBs.begin(),
                 [](const auto &object) { return AABB(object.get()); });
  return AABBs;
}
