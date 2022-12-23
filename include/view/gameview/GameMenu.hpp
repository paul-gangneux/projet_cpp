#ifndef VIEW_GAMEMENU_HPP
#define VIEW_GAMEMENU_HPP

#include "view/drawobject/DrawText.hpp"
#include "view/gameview/DrawableState.hpp"

#define EVENT_SELECT_MENU 10
#define EVENT_SELECT_DOMINO 11
#define EVENT_SELECT_TRAX 12
#define EVENT_SELECT_CARCASSONE 13

class GameMenu : public DrawableState {
 private:
  DrawText menuText;

 public:
  GameMenu(Win* win);
  virtual ~GameMenu();

  virtual int handleEvents(sf::Event& event);
  virtual void changeState();
  virtual void draw();
};

#endif