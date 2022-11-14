#ifndef GEOMETRY_VECTORS_HPP
#define GEOMETRY_VECTORS_HPP

// inspired from the GLM library

//TODO: use class instead ?

typedef struct {
  float x, y;
} vec2;

vec2 operator +(const vec2& v1, const vec2& v2);
vec2 operator -(vec2& v1, vec2& v2);
vec2 operator +=(vec2& v1, vec2& v2);

#endif