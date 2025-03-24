#include "Position.h"
#include "Snake.h"
#include "PlayGround.h"
#include "SDL_utils.h"
#include<iostream>
#include<cmath>
#include "AudioManager.h"

const CellSize CELL_SIZE = {24,24};

using namespace std;
Snake::Snake(PlayGround* playGround_, AudioManager* audioManager_)
: playGround(playGround_),
  direction(Direction::RIGHT),
   audioManager(audioManager_)  // Khởi tạo audioManager
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
      bool ateNote=false;

      if(!inputQueue.empty())
      {
          UserInput input=inputQueue.front(); // lay lenh dau tien ra
          inputQueue.pop(); // xoa lenh do
          direction=changeDirection(input); // Thay doi huong
      }
      int newX=body.front().getx();
      int newY=body.front().gety();
      cout << "Tọa độ đầu rắn: (" << newX << ", " << newY << ")" << endl; // Thêm dòng này
      switch(direction){
      case Direction::UP: newY--;break;
      case Direction::DOWN:newY++;break;
      case Direction::LEFT:newX--;break;
      case Direction::RIGHT:newX++;break;
      }
      Position newHead (newX,newY);
      int piNewX = newX*CELL_SIZE.width;
      int piNewY = newY*CELL_SIZE.height;
      Position piNewHead(piNewX,piNewY);

if (!piNewHead.isInsideBox(0, 0,SCREEN_WIDTH, SCREEN_HEIGHT )) {
    playGround->stopGame();
    return false;
}

   // Kiem tra va cham voi than ran
  for(int i=1;i<body.size();i++){
    if(newHead.getx()==body[i].getx()&&newHead.gety()==body[i].gety()){
        playGround->stopGame();
        return false;
    }
  }

  const vector<Position>& notes = playGround->getNotes();
    for (const Position& note : notes) {
        if (newHead.getx() == note.getx() && newHead.gety() == note.gety()) {
            ateNote = true;
            break; // Ăn một nốt nhạc thì thoát khỏi vòng lặp
        }
    }

  body.insert(body.begin(),newHead);
  if(!ateNote){
    body.pop_back();
  }

  return ateNote;
  }

   void Snake::eatNote() {
    //co the them diem so o day
    cout<<"Ran da an not nhac"<<endl;
    Position head = body.front();
    for (size_t i = 0; i < playGround->getNotes().size(); ++i) {
            Position note = (playGround->getNotes())[i];
             if (head.getx() == note.getx() && head.gety() == note.gety()) {
                     audioManager->playRandomNoteChunk();
                    playGround->removeNote(note);
                    playGround->generateNewNote(body);
                     break;
             }
    }

  }

  Direction Snake::getDirection() const {
      return direction;
  }

  const vector<Position>& Snake::getBody() const{
   return body;
  }

  double Snake::getRotationAngle() const {
    switch (direction) {
        case Direction::UP: return 90.0;
        case Direction::DOWN: return -90.0;
        case Direction::LEFT: return 0.0;
        case Direction::RIGHT: return 180.0;
        default: return 0.0; // Giá trị mặc định
    }
}
