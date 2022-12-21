#ifndef VIEW_GAMEVIEW_HPP
#define VIEW_GAMEVIEW_HPP

#include <iostream>
#include <list>
#include "geometry/vectors.hpp"
#include "view/DrawableState.hpp"
#include "view/Win.hpp"
#include "view/drawobject/DrawDomino.hpp"
#include "view/drawobject/DrawObject.hpp"
#include "view/drawobject/DrawText.hpp"
#include "model/game/Game.hpp"

class GameView : public DrawableState {
 private:
  DrawObject rootObj = DrawObject();
  DrawObject potentialTile = DrawObject();
  DrawObject curTile = DrawObject();
  Game* game;
  std::list<DrawObject*> objects = std::list<DrawObject*>();

  vec2i coordToGridPos(vec2i coords);

 public:
  GameView(Win* win);
  ~GameView();

  void addObject(DrawObject* obj);
  void addTile(DrawObject* obj, int x, int y);
  void addTile(DrawObject* obj, int x, int y, float rotation);

  void clearObjects();
  void viewLoop();

  virtual void handleEvents();
  virtual void changeState();
  virtual void draw();
};

#endif