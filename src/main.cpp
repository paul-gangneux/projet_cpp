#include <iostream>
#include "view/GameView.hpp"
#include "view/DrawText.hpp"
#include "view/DrawDomino.hpp"
#include "view/Win.hpp"
#include "geometry/vectors.hpp"
#include <list>

using namespace sf;
using namespace std;

int main() {
  GameView view{800, 600, "game"};

  DrawDomino* domino = new DrawDomino();
  view.addTile(domino, 0, 0);
  view.addTile(new DrawDomino(), 1, 0);
  view.addTile(new DrawDomino(), 0, 1);
  view.addTile(new DrawDomino(), -1, -1);

  view.viewLoop();

  return EXIT_SUCCESS;
}