#ifndef SNAKE_H
#define SNAKE_H
#include "Position.h"
#include "PlayGround.h"
#include <queue>
#include "AudioManager.h"
#include "EffectManager.h"

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
     EffectManager* effectManager;
     float speed;
     int pennaltyTimer;
     static constexpr float MIN_SPEED = 0.3f;
     float speedAccumulator; // Tích lũy tốc độ
 public:
    Snake(PlayGround* playGround_,AudioManager* audioManager_,EffectManager* effectManager);

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

    void reduceSpeed();

    void update();

    float getSpeed() const ;

    void restoreSpeed(); // Thêm hàm mới để hồi phục tốc độ
};
#endif // SNAKE_H
