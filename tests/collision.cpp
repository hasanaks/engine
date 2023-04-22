#include "doctest.h"

#include "../Collision.hpp"

TEST_CASE("Overlap") {
  PhysicsObject object1{};
  object1.transform = {100, 100};

  PhysicsObject object2{};
  object2.position = {10, -10};
  object1.transform = {100, 100};

  AABB box1(&object1);
  AABB box2(&object2);

  CHECK(isOverlapping(box1, box2));
}
