#include "World.hpp"

World::World(Vector2f gravity) : gravity(gravity) {}

void World::Step(float dt) {
  Echoes();
  gebouw();
  for (auto &physicsObject : physicsObjects) {
    physicsObject->force += physicsObject->mass * gravity;

    auto acceleration = physicsObject->force / physicsObject->mass;
    physicsObject->position +=
        physicsObject->velocity * dt + 0.5f * acceleration * dt * dt;
    physicsObject->velocity += acceleration * dt;

    physicsObject->force = {0, 0};
  }
}

void World::AddParticle(const std::shared_ptr<PhysicsObject> &physicsObject) {
  if (std::find(physicsObjects.begin(), physicsObjects.end(), physicsObject) ==
      std::end(physicsObjects)) {
    physicsObjects.push_back(physicsObject);
  }
}

void World::RemoveParticle(
    const std::shared_ptr<PhysicsObject> &physicsObject) {
  physicsObjects.erase(
      std::remove(physicsObjects.begin(), physicsObjects.end(), physicsObject),
      physicsObjects.end());
}

void World::setBoxList() {
  std::vector<AABB> l1(physicsObjects.size());
  std::transform(physicsObjects.cbegin(), physicsObjects.cend(), l1.begin(), BuildBox);
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

AABB World::BuildBox(std::shared_ptr<PhysicsObject> pickle) {
  AABB box{};
  box.id = pickle;
  box.min = pickle->position - Vector2f{0, pickle->transform.y()};
  box.max = pickle->position + Vector2f{pickle->transform.x(), 0};
  return box;
}

std::vector<PhysicsObject> World::CopyState() {
  std::vector<PhysicsObject> copied(physicsObjects.size());
  std::transform(physicsObjects.cbegin(), physicsObjects.cend(), copied.begin(),
                 [](const auto &physicsObject) { return *physicsObject; });
  return copied;
}
