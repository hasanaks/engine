#pragma once

struct Vector2f {
  float x, y;
};

Vector2f operator+(const Vector2f &lhs, const Vector2f &rhs);
Vector2f operator-(const Vector2f &lhs, const Vector2f &rhs);
Vector2f operator*(const Vector2f &lhs, const float &rhs);
Vector2f operator*(const float &lhs, const Vector2f &rhs);
Vector2f operator/(const Vector2f &lhs, const float &rhs);
Vector2f operator-(const Vector2f &rhs);
void operator+=(Vector2f &lhs, const Vector2f &rhs);
void operator-=(Vector2f &lhs, const Vector2f &rhs);
void operator*=(Vector2f &lhs, const float& rhs);
bool operator==(const Vector2f &lhs, const Vector2f &rhs);
bool operator!=(const Vector2f &lhs, const Vector2f &rhs);
