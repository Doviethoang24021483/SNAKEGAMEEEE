#include "note.h"
using namespace std;

Note::Note(int x_, int y_, string name_)
: x(x_),y(y_),name(name_){}

 int Note::getX() const {
   return x;
 }
 int Note::getY() const {
   return y;
 }
string Note::getName() const{
  return name;
 }
