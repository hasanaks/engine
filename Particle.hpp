#pragma once
#include "Eigen/Dense"

using Eigen::Vector2f;

struct Particle {
  Vector2f position;
  Vector2f velocity;
  Vector2f force;
  float mass;
};
