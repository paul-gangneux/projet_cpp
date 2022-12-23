#ifndef MODEL_PLAYER_HPP
#define MODEL_PLAYER_HPP

#include <string>

class Player {
 private:
  std::string name;
  int score;

 public:
  Player();
  Player(std::string _name);
  Player(int);
  virtual ~Player();
  void addScore(int);
};

#endif