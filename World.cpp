#include "World.hpp"

World::World(Vector2f gravity) : gravity(gravity) {}

void World::Step(float dt) {
  ResolveCollisions();

  std::for_each(physicsObjects.begin(), physicsObjects.end(),
                [dt, this](auto &physicsObject) {
                  physicsObject->force += physicsObject->mass * gravity;

                  auto acceleration =
                      physicsObject->force / physicsObject->mass;
                  physicsObject->position += physicsObject->velocity * dt +
                                             0.5f * acceleration * dt * dt;
                  physicsObject->velocity += acceleration * dt;

                  physicsObject->force = {0, 0};
                });
}

void World::AddParticle(const std::shared_ptr<PhysicsObject> &physicsObject) {
  physicsObjects.insert(physicsObject);
}

void World::RemoveParticle(
    const std::shared_ptr<PhysicsObject> &physicsObject) {
  physicsObjects.erase(physicsObject);
}

std::vector<PhysicsObject> World::CopyState() {
  std::vector<PhysicsObject> copied(physicsObjects.size());
  std::transform(physicsObjects.cbegin(), physicsObjects.cend(), copied.begin(),
                 [](const auto &physicsObject) { return *physicsObject; });
  return copied;
}

void World::ResolveCollisions() {
  auto overlappingBoxes = FindOverlappingBoxes(GetAABBs());

  std::vector<ImpulseSolver> solvers(overlappingBoxes.size(),
                                     ImpulseSolver(nullptr, nullptr));
  std::transform(
      overlappingBoxes.cbegin(), overlappingBoxes.cend(), solvers.begin(),
      [](const auto &overlappingBox) {
        return ImpulseSolver{overlappingBox.first.id, overlappingBox.second.id};
      });

  std::for_each(solvers.begin(), solvers.end(),
                [](auto &solver) { solver.Imp(); });
}

std::vector<AABB> World::GetAABBs() {
  std::vector<AABB> AABBs(physicsObjects.size());
  std::transform(physicsObjects.cbegin(), physicsObjects.cend(), AABBs.begin(),
                 [](const auto &object) { return AABB(object.get()); });
  return AABBs;
}
