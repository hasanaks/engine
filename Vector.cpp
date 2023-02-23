#include "Vector.hpp"

Vector2 operator+(const Vector2& lhs, const Vector2& rhs) {
  return {lhs.x + rhs.x, lhs.y + rhs.y};
}

Vector2 operator-(const Vector2& lhs, const Vector2& rhs) {
  return lhs + (-rhs);
}

Vector2 operator*(const Vector2& lhs, const float& rhs) {
  return {lhs.x * rhs, lhs.y * rhs};
}

Vector2 operator*(const float& lhs, const Vector2& rhs) {
  return rhs * lhs;
}

Vector2 operator/(const Vector2& lhs, const float& rhs) {
  return lhs * (1 / rhs);
}

Vector2 operator-(const Vector2& rhs) {
  return {-rhs.x, -rhs.y};
}

void operator+=(Vector2& lhs, const Vector2& rhs) {
  lhs = lhs + rhs;
}

void operator-=(Vector2& lhs, const Vector2& rhs) {
  lhs = lhs - rhs;
}

void operator*=(Vector2& lhs, const float& rhs) {
  lhs = lhs * rhs;
}

bool operator==(const Vector2& lhs, const Vector2& rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator!=(const Vector2& lhs, const Vector2& rhs) {
  return !(lhs == rhs);
}
