#pragma once
#include <raylib.h>

Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
Vector2 operator*(const Vector2& lhs, const float& rhs);
Vector2 operator*(const float& lhs, const Vector2& rhs);
Vector2 operator/(const Vector2& lhs, const float& rhs);
Vector2 operator-(const Vector2& rhs);
void operator+=(Vector2& lhs, const Vector2& rhs);
void operator-=(Vector2& lhs, const Vector2& rhs);
void operator*=(Vector2& lhs, const float rhs);
bool operator==(const Vector2& lhs, const Vector2& rhs);
bool operator!=(const Vector2& lhs, const Vector2& rhs);
