#pragma once

#include "Eigen/Dense"
#include "PhysicsObject.hpp"
#include <cmath>
#include <memory>
#include <vector>

using Eigen::Vector2f;

struct AABB {
  std::shared_ptr<PhysicsObject> id;
  Vector2f min;
  Vector2f max;
};

struct debut {

  AABB b1;
  AABB b2;
};

struct knife_edge {
  AABB box;
  int b;
  int mag;
};

bool isOverlapping(const AABB &a, const AABB &b);
void isActive(std::vector<debut> &activeList);

std::vector<knife_edge> EdgeInit(std::vector<AABB> boxes);
std::vector<debut> relayer(std::vector<knife_edge> elp);
