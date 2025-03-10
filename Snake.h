#ifndef SNAKE_H
#define SNAKE_H
#include "Position.h"
#include "PlayGround.h"
#include<queue>

enum Direction{
  UP,
  DOWN,
  RIGHT,
  LEFT
};
enum UserInput{
  NO_INPUT,
  KEY_UP,
  KEY_DOWN,
  KEY_LEFT,
  KEY_RIGHT
};

class Snake{
 private:
     Direction direction;
     PlayGround* playGround;
     Position pos;
     queue<UserInput> inputQueue;
 public:
    Snake(PlayGround* playGround_);
    void processUserInput (UserInput input);
    Direction changeDirection(UserInput input);
    void nextStep();
    Position getPosition()const;
    Direction getDirection() const;
};
#endif // SNAKE_H
