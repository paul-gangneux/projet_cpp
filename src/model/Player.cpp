#include "model/Player.hpp"

using namespace std;

Player::Player() : name{"John Gaming"}, score{0} {}

Player::Player(string _name) : name{_name}, score{0} {}

Player::Player(int n) : name{"Player " + to_string(n)}, score{0} {}

Player::~Player() {}

void Player::addScore(int s) {
  score += s;
}

void Player::setName(std::string _name) {
  name = _name;
}

string Player::getName() const {
  return name;
}

int Player::getScore() const {
  return score;
}
