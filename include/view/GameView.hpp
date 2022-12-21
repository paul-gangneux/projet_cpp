#ifndef VIEW_VIEW_HPP
#define VIEW_VIEW_HPP

#include <iostream>
#include "view/drawobject/DrawObject.hpp"
#include "view/drawobject/DrawText.hpp"
#include "view/drawobject/DrawDomino.hpp"
#include "view/Win.hpp"
#include "geometry/vectors.hpp"
#include <list>

class GameView
{
private:
  DrawObject rootObj = DrawObject();
  std::list<DrawObject*> objects = std::list<DrawObject*>();
  Win win;

  vec2i coordToGridPos(vec2i coords);
public:
  GameView(int _w, int _h, const char* windowTitle);
  ~GameView();

  void addObject(DrawObject* obj);
  void addTile(DrawObject* obj, int x, int y);
  void addTile(DrawObject* obj, int x, int y, float rotation);

  void clearObjects();
  void viewLoop();
};


#endif