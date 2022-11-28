#ifndef MODEL_RELATIVEVECTOR_HPP
#define MODEL_RELATIVEVECTOR_HPP
#include "Tile.hpp"

#include <vector>

// relative vector for tiles
template<typename T> class RelativeVector {
private:
  std::vector<T> pos;
  std::vector<T> neg;

public:
  RelativeVector() {} // auto initialization
  ~RelativeVector() {} // todo, maybe

  T& operator[](int x) {
    if (x >= 0)
      return pos[x];
    x = -x - 1;
    return neg[x];
  }

  bool outOfBounds(int x) const {
    if (x >= 0)
      return x >= (int) pos.size();
    return (-x - 1) >= (int) neg.size();
  }
};

#endif