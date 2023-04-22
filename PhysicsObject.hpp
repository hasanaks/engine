#pragma once
#include "Eigen/Dense"

using Eigen::Vector2f;

struct PhysicsObject {
  float mass;
  Vector2f position;
  Vector2f velocity;
  Vector2f force;
  Vector2f transform;
};
