#ifndef VIEW_PLAYERSELECTIONMENU_HPP
#define VIEW_PLAYERSELECTIONMENU_HPP

#include "view/drawobject/TextBox.hpp"
#include "view/gameview/DrawableState.hpp"

class PlayerSelectionMenu : public DrawableState {
 private:
  DrawText text;
  TextBox textBoxes[4];
  int minPlayers;
  int maxPlayers;
  int selectedAction;
  int gameNb;
  int* nbOfPlayers;

  void switchSelectedAction(int action);

 public:
  PlayerSelectionMenu(Win* win, int game, int* nbOfPlayers);
  virtual ~PlayerSelectionMenu();

  virtual int handleEvents(sf::Event& event);
  virtual void changeState();
  virtual void draw();
};

#endif