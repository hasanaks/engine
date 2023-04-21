#include "../Collision.hpp"
#include "doctest.h"

TEST_CASE("Overlap") {
  AABB box1{nullptr, {0, 100}, {100, 0}};
  AABB box2{nullptr, {10, 10}, {20, 20}};

  CHECK(isOverlapping(&box1, &box2));
}
