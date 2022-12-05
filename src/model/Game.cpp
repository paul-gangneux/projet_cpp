#include "model/Game.hpp"
#include <iostream>

Game::Game() :
    players{std::vector<Player*>()},
    board{Board()},
    currentPlayer{0}
{}

Game::~Game() {
    for (Player* p : players) {
        delete p;
    }
}

std::vector<Player*> const Game::getPlayers() const{
    return players;
}

bool Game::canAddNewPlayer() {
    // --- DEBUG
    std::cout << std::endl << "FUCK: Game::canAddNewPlayer() should never be directly called" << std::endl;
    std::exit(1);
    // --- end debug
    return false;
}

bool Game::addPlayer() {
    if (!canAddNewPlayer()) return false;
    Player* p = new Player();
    if (p == nullptr) return false;
    players.push_back(p);
    return true;
}

void Game::nextTurn() {
    currentPlayer = (currentPlayer + 1) % players.size();
}
