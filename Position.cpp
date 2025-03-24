
#include "Position.h"
#include<iostream>
using namespace std;

Position::Position(int x_, int y_):x(x_),y(y_){}

bool Position::isInsideBox(int left, int top, int w, int h){
 if(x>=left && x<left+w&& y>=top&&y<top+h) return true;

 return false;
}

int Position::getx() const{
  return x;
}

int Position::gety() const {
  return y;
}

