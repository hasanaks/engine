#pragma once
#include "Vector.hpp"

struct Particle {
  Vector2f position;
  Vector2f velocity;
  Vector2f force;
  Vector2f acceleration;
  float mass;
};
