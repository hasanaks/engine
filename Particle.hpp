#pragma once
#include <raylib.h>

struct Particle {
  Vector2 position;
  Vector2 velocity;
  Vector2 force;
  float mass;
};
