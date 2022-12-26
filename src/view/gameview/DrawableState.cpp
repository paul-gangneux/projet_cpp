#include "view/gameview/DrawableState.hpp"

DrawableState::DrawableState(Win* _win) : win{_win}, rootObj{DrawObject()} {
  win->setRootObject(&rootObj);
  rootObj.setPosition(win->getWidth() / 2, win->getHeight() / 2);
}

DrawableState::~DrawableState() {}