#include "Position.h"
#include "Snake.h"
#include "PlayGround.h"
#include<iostream>
using namespace std;
Snake::Snake(PlayGround* playGround)
: playGround(playGround),
  direction(RIGHT)
  {
  int startX = playGround->getWidth()/2;
  int startY = playGround->getHeight()/2;
   pos=Position(startX, startY);
  }
  void Snake::processUserInput(UserInput input){
      if(input!=NO_INPUT)
    inputQueue.push(input);
  }
  Direction Snake::changeDirection(UserInput input){
    if (input == KEY_UP && direction != DOWN) return UP;
    if (input == KEY_DOWN && direction != UP) return DOWN;
    if (input == KEY_LEFT && direction != RIGHT) return LEFT;
    if (input == KEY_RIGHT && direction != LEFT) return RIGHT;
    return direction; // Giữ nguyên hướng nếu input không hợp lệ
}
  void Snake::nextStep(){
      if(!inputQueue.empty())
      {
          UserInput input=inputQueue.front();
          inputQueue.pop();
          direction=changeDirection(input);
      }
      Position newpos = pos;
      switch(direction){
      case UP: newpos=pos.gety()+1;break;
      case DOWN:newpos=pos.gety()-1;break;
      case LEFT:newpos=pos.getx()-1;break;
      case RIGHT:newpos=pos.getx()+1;break;
      }
if(newpos.isInsideBox(0,0,playGround->getWidth(),playGround->getHeight()))
  {
      playGround->changeCellType(CELLEMPTY,pos);
        pos=newpos;
      playGround->changeCellType(CELLSNAKE,newpos);
  }
  }
  Position Snake::getPosition() const{
      return pos;
  }
  Direction Snake::getDirection() const {
      return direction;
  }
