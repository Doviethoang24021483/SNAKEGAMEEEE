#include "Position.h"
#include "Snake.h"
#include "PlayGround.h"
#include<iostream>
using namespace std;
Snake::Snake(PlayGround* playGround)
: playGround(playGround),
  direction(Direction::RIGHT)
  {
  int startX = playGround->getWidth()/2;
  int startY = playGround->getHeight()/2;
   body.push_back(Position(startX, startY));
  }

  void Snake::processUserInput(UserInput input){
      if(input!=UserInput::NO_INPUT)
    inputQueue.push(input);
  }
  Direction Snake::changeDirection(UserInput input){
    if (input == UserInput::KEY_UP && direction != Direction::DOWN) return UP;
    if (input == UserInput::KEY_DOWN && direction != Direction::UP) return DOWN;
    if (input == UserInput::KEY_LEFT && direction != Direction::RIGHT) return LEFT;
    if (input == UserInput::KEY_RIGHT && direction != Direction::LEFT) return RIGHT;
    return direction; // Giữ nguyên hướng nếu input không hợp lệ
}
  bool Snake::nextStep(){
      bool ateCherry=false;
      if(!inputQueue.empty())
      {
          UserInput input=inputQueue.front();
          inputQueue.pop();
          direction=changeDirection(input);
      }
      int newX=body.front().getx();
      int newY=body.front().gety();
      switch(direction){
      case Direction::UP: newY--;break;
      case Direction::DOWN:newY++;break;
      case Direction::LEFT:newX--;break;
      case Direction::RIGHT:newX++;break;
      }
      Position newHead(newX,newY);
if(!newHead.isInsideBox(0,0,playGround->getWidth(),playGround->getHeight()))
  {
      playGround->stopGame();
      return false;
  }
  for(int i=1;i<body.size();i++){
    if(newHead.getx()==body[i].getx()&&newHead.gety()==body[i].gety()){
        playGround->stopGame();
        return false;
    }
  }
  if(newHead.getx()==playGround->getCherry().getx()&&newHead.gety()==playGround->getCherry().gety()){
    eatCherry();
    playGround->generateCherry(body);
    ateCherry=true;
  }
  body.insert(body.begin(),newHead);
  if(!ateCherry){
    body.pop_back();
  }
  return ateCherry;
  }
  void Snake::eatCherry(){
      //co the them diem so o day
    cout<<"Ran da an cherry"<<endl;
  }

  Direction Snake::getDirection() const {
      return direction;
  }
  const vector<Position>& Snake::getBody() const{
   return body;
  }
