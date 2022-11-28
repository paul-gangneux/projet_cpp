#include "model/TileDomino.hpp"
#include <iostream>
#include <ctime>

TileDomino::TileDomino() :
  T{new int[12]}
{
  std::srand(std::time(nullptr));
  for (int i=0; i<12; i++){
    T[i]=rand()%5;
  }
}

TileDomino::~TileDomino(){
  delete T;
}

// If you are confused on how the following functions work, please check TileDomino.hpp
  
void TileDomino::rotateClockwise(){
  int temp[3] = {T[9],T[10],T[11]};
  for (int i=11; i>2; i--){
    T[i]=T[(i+9)%12];
  }
  for (int i=0; i<3; i++){
    T[i]=temp[i];
  }
}

void TileDomino::rotateCounterClockwise(){
  int temp[3] = {T[0],T[1],T[2]};
  for (int i=0; i<9; i++){
    T[i]=T[i+3];
  }
  for (int i=9; i<12; i++){
    T[i]=temp[i-9];
  }
}