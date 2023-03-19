#pragma once
#include "Vector.hpp"

struct Particle {
  Vector2f position;
  Vector2f velocity;
  Vector2f force;
  float mass;
};
