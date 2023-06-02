#include "Math.hpp"

Eigen::Vector2f Lerp(const Eigen::Vector2f &a, const Eigen::Vector2f &b, float alpha) {
  return (1 - alpha) * a + alpha * b;
}
