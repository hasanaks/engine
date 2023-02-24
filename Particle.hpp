#pragma once
#include <raylib.h>

struct Particle {
  Vector2 position;
  Vector2 velocity;
  Vector2 force;
  Vector2 acceleration;
  float mass;
};
