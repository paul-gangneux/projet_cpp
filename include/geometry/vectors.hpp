#ifndef GEOMETRY_VECTORS_HPP
#define GEOMETRY_VECTORS_HPP

#include <iostream>

// inspired from the GLM library

// float vector of size 2
typedef struct {
  float x, y;
} vec2;

// operator redefinitions
// notes:
//     there is no need to redefine =
//     it doesn't make sense to redefine < or >

// addition / substraction

vec2 operator +(const vec2& v1, const vec2& v2);
vec2 operator -(const vec2& v1, const vec2& v2);
vec2& operator +=(vec2& v1, const vec2& v2);
vec2& operator -=(vec2& v1, const vec2& v2);

// inverse

vec2 operator -(const vec2& v);

// scalar multiplication

vec2 operator *(const vec2& v, const float& s);
vec2 operator *(const float& s, const vec2& v);
vec2& operator *=(vec2& v, const float& s);

// scalar division

vec2 operator /(const vec2& v, const float& s);
vec2& operator /=(vec2& v, const float& s);

// stream operator

std::ostream& operator <<(std::ostream& out, const vec2& v);

#endif