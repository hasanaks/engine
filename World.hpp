#pragma once

#include "Collision.hpp"
#include "Constraint.hpp"
#include "ImpulseSolver.hpp"
#include "PhysicsObject.hpp"
#include <algorithm>
#include <memory>
#include <unordered_set>
#include <vector>

class World {
public:
  explicit World(Vector2f gravity);
  void Step(float dt);
  void AddPhysicsObject(const std::shared_ptr<PhysicsObject> &physicsObject);
  void RemovePhysicsObject(const std::shared_ptr<PhysicsObject> &physicsObject);
  std::vector<PhysicsObject> CopyState();

  Vector2f gravity{0};

private:
  void UpdatePhysicsObject(const std::shared_ptr<PhysicsObject>& physicsObject, float dt);
  void ResolveCollisions();
  std::vector<AABB> GetAABBs();

  std::unordered_set<std::shared_ptr<PhysicsObject>> physicsObjects;
  std::vector<ImpulseSolver> constraints;
};
