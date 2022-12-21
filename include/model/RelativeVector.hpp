#ifndef MODEL_RELATIVEVECTOR_HPP
#define MODEL_RELATIVEVECTOR_HPP

#include <functional>
#include <vector>

// relative vector for tiles
template <typename T>
class RelativeVector {
 private:
  std::vector<T> pos;
  std::vector<T> neg;

 public:
  RelativeVector() : pos{std::vector<T>()}, neg{std::vector<T>()} {}
  ~RelativeVector() {}  // todo, maybe

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

  // expands vector if index is out of bound
  void expand(int last_index) {
    if (outOfBounds(last_index)) {
      if (last_index < 0) {
        last_index = -last_index - 1;
        neg.resize(last_index + 1);
      } else {
        pos.resize(last_index + 1);
      }
    }
  }

  void forEach(std::function<void(T)> f) {
    for (T t : neg) {
      f(t);
    }
    for (T t : pos) {
      f(t);
    }
  }
};

#endif