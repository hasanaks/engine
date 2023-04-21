#pragma once

#include "ImpulseSolver.hpp"
#include "Collision.hpp"
#include "Constraint.hpp"
#include "Particle.hpp"
#include <algorithm>
#include <memory>
#include <vector>

class World {
public:
  explicit World(Vector2f gravity);
  void Step(float dt);
  void AddParticle(std::shared_ptr<PhysicsObject> particle);
  void RemoveParticle(std::shared_ptr<PhysicsObject> particle);
  std::vector<PhysicsObject> CopyState();
  static AABB BuildBox(std::shared_ptr<PhysicsObject> pickle);
  void setBoxList();
  Vector2f gravity{0};
  void Echoes();
  void gebouw();

private:
  std::vector<std::shared_ptr<PhysicsObject>> particles;
  std::vector<debut> activeList;
  std::vector<ImpulseSolver> constraints;
};
