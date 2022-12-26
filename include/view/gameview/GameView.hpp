#ifndef VIEW_GAMEVIEW_HPP
#define VIEW_GAMEVIEW_HPP

#include <iostream>
#include <list>

#include "geometry/vectors.hpp"
#include "model/game/Game.hpp"
#include "view/Win.hpp"
#include "view/drawobject/DrawDomino.hpp"
#include "view/drawobject/DrawObject.hpp"
#include "view/drawobject/DrawText.hpp"
#include "view/gameview/DrawableState.hpp"

class GameView : public DrawableState {
 protected:
  Game* game;
  DrawObject* tilePlacementVisual;
  DrawObject* curTile;
  DrawText* topLeftText;

  std::list<DrawObject*> objects;
  std::list<DrawText*> textList;

  // mouse data

  vec2i oldMousePos;
  vec2i mousePos;
  vec2i deltaMouse;

  // used for events

  bool validM1Press;
  bool validM2Press;
  bool leftRotPress;
  bool rightRotPress;

  bool firstPlay;

  // used for tile rotation

  float curRot;
  float destRot;

  int modelRot;

  vec2i coordToGridPos(vec2i coords);
  DrawObject* initTilePlacementVisual();

  GameView(Win* win, Game* game, DrawObject* firstTile);

 public:
  virtual ~GameView();

  void addObject(DrawObject* obj);
  void addTile(DrawObject* obj, int x, int y);
  void addTile(DrawObject* obj, int x, int y, float rotation);

  void clearObjects();
  void clearText();

  virtual int handleEvents(sf::Event& event);
  virtual void changeState();
  virtual void draw();

  // deals with all key press events that arent default
  virtual int onKeyPress(sf::Event& event) = 0;
};

#endif