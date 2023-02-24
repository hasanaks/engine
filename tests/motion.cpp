#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include "../World.hpp"

TEST_CASE("particle motion physics") {
  World world;

  auto particle = std::make_shared<Particle>();
  particle->mass = 10;

  world.AddParticle(particle);
  world.Step(1);

  CHECK(particle->force == Vector2{0, 0});
  CHECK(particle->position == Vector2{0, -5});
  CHECK(particle->velocity == Vector2{0, -10});
}
