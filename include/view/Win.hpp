#ifndef VIEW_WIN_HPP
#define VIEW_WIN_HPP

#include <SFML/Graphics.hpp>

class Win : public sf::RenderWindow {
private:
  int width, height;
public:
  Win(int width, int height, const char* name);
  virtual ~Win();
protected:
  virtual void onResize();
};

#endif