#ifndef GEOMETRY_VECTORS_HPP
#define GEOMETRY_VECTORS_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

// shorter names

// float vector
typedef sf::Vector2f vec2f;

// signed int vector
typedef sf::Vector2i vec2i;

// unigned int vector
typedef sf::Vector2u vec2u;

// stream operator

template <typename T>
std::ostream& operator <<(std::ostream& out, const sf::Vector2<T>& v) {
  return out << v.x << ", " << v.y;
}

template <typename T>
std::string to_string(sf::Vector2<T> v) {
  return std::to_string(v.x) + " " + std::to_string(v.y);
}

#endif