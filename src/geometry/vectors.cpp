#include "geometry/vectors.hpp"

// addition / substraction

vec2 operator +(const vec2& v1, const vec2& v2) {
  return vec2{v1.x + v2.x, v1.y + v2.y};
}

vec2 operator -(const vec2& v1, const vec2& v2) {
  return vec2{v1.x - v2.x, v1.y - v2.y};
}

vec2& operator +=(vec2& v1, const vec2& v2) {
  v1.x += v2.x;
  v1.y += v2.y;
  return v1;
}

vec2& operator -=(vec2& v1, const vec2& v2) {
  v1.x -= v2.x;
  v1.y -= v2.y;
  return v1;
}

// inverse

vec2 operator -(const vec2& v) {
  return vec2{-v.x, -v.y};
}

// scalar multiplication

vec2 operator *(const vec2& v, const float& s) {
  return vec2{v.x * s, v.y * s};
}

vec2 operator *(const float& s, const vec2& v) {
  return vec2{v.x * s, v.y * s};
}

vec2& operator *=(vec2& v, const float& s) {
  v.x *= s;
  v.y *= s;
  return v;
}

// scalar division

vec2 operator /(const vec2& v, const float& s) {
  return vec2{v.x / s, v.y / s};
}

vec2& operator /=(vec2& v, const float& s) {
  v.x /= s;
  v.y /= s;
  return v;
}

// stream operator

std::ostream& operator <<(std::ostream& out, const vec2& v) {
  return out << v.x << ", " << v.y;
}