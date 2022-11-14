#include "geometry/vectors.hpp"

vec2 operator +(const vec2& v1, const vec2& v2) {
  return vec2{v1.x + v2.x, v1.y + v2.y};
}

vec2 operator -(vec2& v1, vec2& v2) {
  return vec2{v1.x - v2.x, v1.y - v2.y};
}

vec2 operator +=(vec2& v1, vec2& v2) {
  v1.x += v2.x;
  v1.y += v2.y;
  return v1;
}