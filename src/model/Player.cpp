#include "model/Player.hpp"

Player::Player() : name{"polggers"}, score{0} {}

Player::Player(std::string _name) : name{_name}, score{0} {}

Player::~Player() {}

void Player::addScore(int s) {
  score += s;
}
