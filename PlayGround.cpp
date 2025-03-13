
#include<iostream>
#include "PlayGround.h"
#include "Position.h"
#include<cassert>
#include<vector>
#include<cstdlib>
#include<ctime>
using namespace std;

PlayGround::PlayGround(int width_, int height_)
: width(width_),height(height_),
squares(height,vector<CellType>(width,CELLEMPTY)),
status(GAMERUNNING),
gameRun(true),
cherry(0,0)
{
 srand(time(0));
 generateCherry({}); //tao vi tri ngau nhien
}
//Tao ra vi tri cherry ngau nhien
void PlayGround::generateCherry(const vector<Position>& snakeBody) {
 Position newCherry;
 bool validPosition = false;
 while(!validPosition){
    int x = rand() % getWidth();
    int y = rand() % getHeight();
    newCherry=Position(x,y);
    validPosition=true;
    for(const Position& segment: snakeBody){
        if(segment.getx() == newCherry.getx() && segment.gety()==newCherry.gety()){
            validPosition = false;
            break;
        }
    }
 }
 setCherry(newCherry);
}

int PlayGround::getWidth() const {
    return width;
}

int PlayGround::getHeight() const{
    return height;
}

Position PlayGround::getCherry() const{
   return cherry;
}

CellType PlayGround::getCellType(Position pos)
{ assert(pos.isInsideBox(0,0,getWidth(),getHeight()));
return squares[pos.gety()][pos.getx()];
}

CellType PlayGround::changeCellType(CellType type, Position pos){
    if(pos.isInsideBox(0,0,getWidth(),getHeight()))
    squares[pos.getx()][pos.gety()]=type;
    return squares[pos.gety()][pos.getx()];
}

bool PlayGround::isGameRun()const{
 return status == GAMERUNNING && gameRun;
}

void PlayGround::setCherry(Position newCherry){
  cherry=newCherry;
}

void PlayGround::stopGame(){
 gameRun = false;
 status = GAMESTOP;
}

void PlayGround::setGameRun(bool run){
  gameRun=run;
}
