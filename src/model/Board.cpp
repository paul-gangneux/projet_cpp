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
  if (
    isEmptySpace(x,y) &&
    isAdjacent(x,y) &&
    ( (board[x-1][y]==nullptr) || (*board[x-1][y]).matchX(tile) ) &&
    ( (board[x+1][y]==nullptr) || (*tile).matchX(board[x+1][y]) ) &&
    ( (board[x][y-1]==nullptr) || (*board[x][y-1]).matchY(tile) ) &&
    ( (board[x][y+1]==nullptr) || (*tile).matchY(board[x][y+1]) )
  ){
    placeTileForced(x,y,tile);
    return true;
  }
  return false;
}
