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
  auto activeBoxes = GetActiveAABB();

  std::vector<ImpulseSolver> solvers(activeBoxes.size(),
                                     ImpulseSolver(nullptr, nullptr));
  std::transform(activeBoxes.cbegin(), activeBoxes.cend(), solvers.begin(),
                 [](const auto &activeBox) {
                   return ImpulseSolver{activeBox.b1.id, activeBox.b2.id};
                 });

  std::for_each(solvers.begin(), solvers.end(),
                [](auto &solver) { solver.Imp(); });
}

std::vector<debut> World::GetActiveAABB() {
  std::vector<AABB> l1(physicsObjects.size());
  std::transform(physicsObjects.cbegin(), physicsObjects.cend(), l1.begin(),
                 [](const auto &object) { return AABB(object.get()); });
  auto activeList = relayer(EdgeInit(l1));
  isActive(activeList);
  return activeList;
}
