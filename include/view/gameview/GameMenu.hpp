#ifndef VIEW_GAMEMENU_HPP
#define VIEW_GAMEMENU_HPP

#include "view/drawobject/TextBox.hpp"
#include "view/gameview/DrawableState.hpp"

#define EVENT_SELECT_MENU 10
#define EVENT_SELECT_DOMINO 11
#define EVENT_SELECT_TRAX 12
#define EVENT_SELECT_CARCASSONNE 13
#define EVENT_SELECT_DOMINO_PLAYERSELECT 14
#define EVENT_SELECT_CARCASSONNE_PLAYERSELECT 15

class GameMenu : public DrawableState {
 private:
  TextBox menuTextBoxes[3];
  int selectedAction;

  void switchSelectedAction(int action);

 public:
  GameMenu(Win* win);
  virtual ~GameMenu();

  virtual int handleEvents(sf::Event& event);
  virtual void changeState();
  virtual void draw();
};

#endif