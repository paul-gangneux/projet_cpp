#include <iostream>
#include "view/GameView.hpp"
#include "view/DrawText.hpp"
#include "view/DrawDomino.hpp"
#include "view/DrawTrex.hpp"
#include "view/Win.hpp"
#include "geometry/vectors.hpp"
#include <list>

using namespace sf;
using namespace std;

int main() {
  GameView view{800, 600, "game"};

  // // tests
  // view.addTile(new DrawTrex(1), 0, 0);
  // view.addTile(new DrawDomino(), 1, 0);
  // view.addTile(new DrawTrex(1), 0, 1);
  // view.addTile(new DrawTrex(2), -1, -1);

  // starting game loop
  view.viewLoop();

  return EXIT_SUCCESS;
}