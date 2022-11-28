#include "model/TileDomino.hpp"
#include <iostream>
#include <ctime>

TileDomino::TileDomino() :
  numbers{new int[12]}
{
  std::srand(std::time(nullptr));
  for (int i=0; i<12; i++){
    numbers[i]=rand()%5;
  }
}

TileDomino::~TileDomino(){
  delete numbers;
}

// If you are confused on how the following functions work, please check TileDomino.hpp
  
void TileDomino::rotateClockwise(){
  int temp[3] = {numbers[9],numbers[10],numbers[11]};
  for (int i=11; i>2; i--){
    numbers[i]=numbers[(i+9)%12];
  }
  for (int i=0; i<3; i++){
    numbers[i]=temp[i];
  }
}

void TileDomino::rotateCounterClockwise(){
  int temp[3] = {numbers[0],numbers[1],numbers[2]};
  for (int i=0; i<9; i++){
    numbers[i]=numbers[i+3];
  }
  for (int i=9; i<12; i++){
    numbers[i]=temp[i-9];
  }
}