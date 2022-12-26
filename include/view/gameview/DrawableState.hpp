#ifndef VIEW_DRAWABLESTATE_HPP
#define VIEW_DRAWABLESTATE_HPP

#include "view/Win.hpp"

#define EVENT_QUIT 1
#define EVENT_BACK 2

class DrawableState {
 protected:
  Win* win;
  DrawObject rootObj;
  DrawableState(Win* win);

 public:
  virtual ~DrawableState();

  // can return EVENT_QUIT or EVENT_BACK, to be done by the main function
  virtual int handleEvents(sf::Event& event) = 0;
  virtual void changeState() = 0;
  virtual void draw() = 0;
};

#endif