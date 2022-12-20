#ifndef VIEW_DRAWABLESTATE_HPP
#define VIEW_DRAWABLESTATE_HPP

#include "view/Win.hpp"

class DrawableState {
 protected:
  Win* win;
  DrawableState(Win* win);

 public:
  
  virtual ~DrawableState() = 0;

  virtual void handleEvents() = 0;
  virtual void changeState() = 0;
  virtual void draw() = 0;
};

#endif