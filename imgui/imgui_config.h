#pragma once

#define IMGUI_DISABLE_OBSOLETE_FUNCTIONS
#define IMGUI_DISABLE_OBSOLETE_KEYIO

#include <Eigen/Core>

#define IM_VEC2_CLASS_EXTRA                                                    \
  ImVec2(const Eigen::Vector2f &f) : x(f.x()), y(f.y()) {}                     \
  operator Eigen::Vector2f() const { return Eigen::Vector2f(x, y); }
#define IM_VEC4_CLASS_EXTRA                                                    \
  ImVec4(const Eigen::Vector4f &f) : x(f.x()), y(f.y()), z(f.z()), w(f.w()) {} \
  operator Eigen::Vector4f() const { return Eigen::Vector4f(x, y, z, w); }
