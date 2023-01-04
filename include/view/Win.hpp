#ifndef VIEW_WIN_HPP
#define VIEW_WIN_HPP

#include <SFML/Graphics.hpp>
#include <view/drawobject/DrawObject.hpp>

class Win : public sf::RenderWindow {
 private:
  int width, height;
  DrawObject* rootObject;

 public:
  Win(int width,
      int height,
      const char* name,
      sf::Uint32 videoMode = sf::Style::Default);
  virtual ~Win();

  int getWidth() const;
  int getHeight() const;

  void setRootObject(DrawObject* object);

 protected:
  virtual void onResize();
};

#endif