#ifndef SNAKE_H
#define SNAKE_H
#include "Position.h"
#include "PlayGround.h"
#include <queue>
#include "AudioManager.h"

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
     AudioManager* audioManager;
 public:
    Snake(PlayGround* playGround_,AudioManager* audioManager_);

    //Them input tu nguoi choi vao hang doi
    void processUserInput (UserInput input);

    //Thay doi huong
    Direction changeDirection(UserInput input);

    //Di chuyen ran 1 buoc
    bool nextStep();

    Direction getDirection() const;

    void eatNote();

    const vector<Position>& getBody() const;

    double getRotationAngle() const;

};
#endif // SNAKE_H
