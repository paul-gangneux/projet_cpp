#ifndef VIEW_GAMEVIEWTraxTRAX_HPP
#define VIEW_GAMEVIEWTraxTRAX_HPP

#include <iostream>
#include <list>
#include "geometry/vectors.hpp"
#include "view/Win.hpp"
#include "view/drawobject/DrawDomino.hpp"
#include "view/drawobject/DrawObject.hpp"
#include "view/drawobject/DrawText.hpp"
#include "view/GameView.hpp"

class GameViewTrax : public GameView {
 private:
  DrawObject rootObj = DrawObject();
  std::list<DrawObject*> objects = std::list<DrawObject*>();

  vec2i coordToGridPos(vec2i coords);

 public:
  GameViewTrax(Win* win);
  ~GameViewTrax();

  void addObject(DrawObject* obj);
  void addTile(DrawObject* obj, int x, int y);
  void addTile(DrawObject* obj, int x, int y, float rotation);

  void clearObjects();
  void viewLoop();

  virtual int handleEvents(sf::Event& event);
  virtual void changeState();
  virtual void draw();
};

#endif