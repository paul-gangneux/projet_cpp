#include <iostream>
#include "view/GameView.hpp"
#include "view/drawobject/DrawText.hpp"
#include "view/drawobject/DrawDomino.hpp"
#include "view/drawobject/DrawTrex.hpp"
#include "view/Win.hpp"
#include "geometry/vectors.hpp"
#include <list>

using namespace sf;
using namespace std;

int main() {
  GameView view{800, 600, "game"};
  view.viewLoop();

  return EXIT_SUCCESS;
}