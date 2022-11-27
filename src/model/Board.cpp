#include "model/Board.hpp"

void Board::placeTileForced(int x, int y, Tile * const tile){
    board[x][y]=tile;
}

bool Board::isEmptySpace(int x, int y){
  return (board[x][y]!=nullptr);
}

bool Board::isAdjacent(int x, int y){
  return ( (!isEmptySpace(x-1,y)) || (!isEmptySpace(x+1,y))
    || (!isEmptySpace(x,y-1)) || (!isEmptySpace(x,y+1)) );
}

bool Board::placeTile(int x, int y, Tile * const tile){
  if (isEmptySpace(x,y) && isAdjacent(x,y)){
    placeTileForced(x,y,tile);
    return true;
  }
  return false;
}
