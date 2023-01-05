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
  void setName(std::string name);

  std::string getName() const;
  int getScore() const;
};

#endif