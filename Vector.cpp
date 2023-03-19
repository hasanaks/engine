#include "Vector.hpp"

Vector2f Vector2f::Interpolate(Vector2f a, Vector2f b, float alpha) {
  return a * (1.f - alpha) + b * alpha;
}

Vector2f operator+(const Vector2f &lhs, const Vector2f &rhs) {
  return {lhs.x + rhs.x, lhs.y + rhs.y};
}

Vector2f operator-(const Vector2f &lhs, const Vector2f &rhs) {
  return lhs + (-rhs);
}

Vector2f operator*(const Vector2f &lhs, const float &rhs) {
  return {lhs.x * rhs, lhs.y * rhs};
}

Vector2f operator*(const float &lhs, const Vector2f &rhs) { return rhs * lhs; }

Vector2f operator/(const Vector2f &lhs, const float &rhs) {
  return lhs * (1 / rhs);
}

Vector2f operator-(const Vector2f &rhs) { return {-rhs.x, -rhs.y}; }

void operator+=(Vector2f &lhs, const Vector2f &rhs) { lhs = lhs + rhs; }

void operator-=(Vector2f &lhs, const Vector2f &rhs) { lhs = lhs - rhs; }

void operator*=(Vector2f &lhs, const float &rhs) { lhs = lhs * rhs; }

bool operator==(const Vector2f &lhs, const Vector2f &rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator!=(const Vector2f &lhs, const Vector2f &rhs) {
  return !(lhs == rhs);
}

float operator*(const Vector2f& lhs, const Vector2f& rhs) {
	float sum = lhs.x * rhs.x + lhs.y * rhs.y;
	return sum;
}