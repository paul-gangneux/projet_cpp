#include "model/TileDomino.hpp"
#include <iostream>
#include <ctime>

void TileDomino::generate3ForArray(int* A){
    A[0]=rand()%5;
    A[1]=rand()%5;
    A[2]=rand()%5;
}

TileDomino::TileDomino() :
    T{new int[3]},
    R{new int[3]},
    B{new int[3]},
    L{new int[3]}
{
    // note: this is lame. i'll probably code it in a better way eventually
    std::srand(std::time(nullptr));
    generate3ForArray(T);
    generate3ForArray(R);
    generate3ForArray(B);
    generate3ForArray(L);
}

TileDomino::~TileDomino(){
    delete T;
    delete R;
    delete B;
    delete L;
}
  
void TileDomino::rotateClockwise(){
    int* temp=T;
    T=L;
    L=B;
    B=R;
    R=temp;
}

void TileDomino::rotateCounterClockwise(){
    int* temp=T;
    T=R;
    R=B;
    B=L;
    L=temp;
}