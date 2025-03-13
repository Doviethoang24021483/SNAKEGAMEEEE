
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

Position Position::setx(int newx) const {
 return Position(newx,y);
}
//Tao ra 1 doi tuong Position moi voi y da dc thay doi an toan, de go loi, de bao tri
Position Position::sety(int newy) const {
 return Position(x,newy);
}

void Position::disPlay() const{
 cout<<x<<" "<<y;
}
