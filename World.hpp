#pragma once

#include "Collision.hpp"
#include "Constraint.hpp"
#include "ImpulseSolver.hpp"
#include "PhysicsObject.hpp"
#include <algorithm>
#include <memory>
#include <vector>
#include <unordered_set>

class World {
public:
  explicit World(Vector2f gravity);
  void Step(float dt);
  void AddParticle(const std::shared_ptr<PhysicsObject> &physicsObject);
  void RemoveParticle(const std::shared_ptr<PhysicsObject> &physicsObject);
  void ResolveCollisions();
  std::vector<PhysicsObject> CopyState();

  Vector2f gravity{0};

private:
  std::vector<AABB> GetAABBs();

  std::unordered_set<std::shared_ptr<PhysicsObject>> physicsObjects;
  std::vector<ImpulseSolver> constraints;
};
