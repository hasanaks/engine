#pragma once

#include "ImpulseSolver.hpp"
#include "Collision.hpp"
#include "Constraint.hpp"
#include "PhysicsObject.hpp"
#include <algorithm>
#include <memory>
#include <vector>

class World {
public:
  explicit World(Vector2f gravity);
  void Step(float dt);
  void AddParticle(const std::shared_ptr<PhysicsObject> &physicsObject);
  void RemoveParticle(const std::shared_ptr<PhysicsObject> &physicsObject);
  std::vector<PhysicsObject> CopyState();
  static AABB BuildBox(std::shared_ptr<PhysicsObject> pickle);
  void setBoxList();
  Vector2f gravity{0};
  void Echoes();
  void gebouw();

private:
  std::vector<std::shared_ptr<PhysicsObject>> physicsObjects;
  std::vector<debut> activeList;
  std::vector<ImpulseSolver> constraints;
};
