#include "model/Board.hpp"

std::vector<std::vector<Tile*>> board;

void placeTileForced(int x, int y, Tile * const tile){
    board[x][y]=tile;
}

bool isEmptySpace(int x, int y){
  return (board[x][y]!=nullptr);
}

bool isAdjacent(int x, int y){
  return ( (!isEmptySpace(x-1,y)) || (!isEmptySpace(x+1,y))
    || (!isEmptySpace(x,y-1)) || (!isEmptySpace(x,y+1)) );
}

bool placeTile(int x, int y, Tile * const tile){
  if (isEmptySpace(x,y) && isAdjacent(x,y)){
    placeTileForced(x,y,tile);
    return true;
  }
  return false;
}
