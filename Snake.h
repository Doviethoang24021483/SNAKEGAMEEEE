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
     vector<Position> body;
     queue<UserInput> inputQueue;
 public:
    //Nhan mot con tro tro den doi tuong playground de tuong tac
    Snake(PlayGround* playGround_);
    //Them input tu nguoi choi vao hang doi
    void processUserInput (UserInput input);
    //Thay doi huong
    Direction changeDirection(UserInput input);
    //Di chuyen ran 1 buoc
    bool nextStep();

    Direction getDirection() const;
    // Xu li khi an cherry
    void eatCherry();
    //Tra ve vi tri cua tung dot ran.
    const vector<Position>& getBody() const;
};
#endif // SNAKE_H
