#include "model/game/GameTrax.hpp"

GameTrax::GameTrax() :
  Game()
{
 
}

GameTrax::~GameTrax() {

}

bool GameTrax::gameOver() {
  return false; //todo
}

bool GameTrax::canAddNewPlayer() {
  return true; //always return true since we can have infinite gamers playing a domino game
}