#include "Position.h"
#include "Snake.h"
#include "PlayGround.h"
#include "SDL_utils.h"
#include<iostream>
#include<cmath>
#include "AudioManager.h"
#include "EffectManager.h"

const CellSize CELL_SIZE = {30,30};
constexpr float Snake::MIN_SPEED; // Định nghĩa MIN_SPEED

using namespace std;
Snake::Snake(PlayGround* playGround_, AudioManager* audioManager_,EffectManager* effectManager)
: playGround(playGround_),
  direction(Direction::RIGHT),
   audioManager(audioManager_),  // Khởi tạo audioManager
    effectManager(effectManager),
    speed(1.0f),pennaltyTimer(0),
    speedAccumulator(0.0f)
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

      // Tích lũy tốc độ
    speedAccumulator += speed;
    if (speedAccumulator >= 1.0f) { // Chỉ di chuyển khi tích lũy đủ
        speedAccumulator -= 1.0f; // Trừ đi phần đã dùng
      if(pennaltyTimer > 0){
        pennaltyTimer --;
        if(pennaltyTimer == 0){
            speed = 1.0f;//Khoi phuc toc do
        }
      }


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

  const vector<Note>& notes = playGround->getNotes();
    for (const Note& note : notes) {
        if (newHead.getx() == note.position.getx() && newHead.gety() == note.position.gety()) {
            if ( note.position.getx() == playGround->getTargetNote().position.getx() && note.position.gety() == playGround->getTargetNote().position.gety() ){
                cout<<"Dung not muc tieu"<<endl;
            }
            else {
                cout<<"Sai not muc tieu"<<endl;
            }
            ateNote = true;
            break; // Ăn một nốt nhạc thì thoát khỏi vòng lặp
        }
    }
  body.insert(body.begin(),newHead);
  if(!ateNote ){
    body.pop_back();
  }
}
  return ateNote;
  }

void Snake::eatNote() {
    Position head = body.front();
    for (size_t i = 0; i < playGround->getNotes().size(); ++i) {
        Note note = (playGround->getNotes())[i];
        if (head.getx() == note.position.getx() && head.gety() == note.position.gety()) {

            // Kiểm tra xem có phải là targetNote hay không
            bool isTargetNote = (note.position.getx() == playGround->getTargetNote().position.getx() &&
                          note.position.gety() == playGround->getTargetNote().position.gety());
           if(isTargetNote == true ) restoreSpeed();
     if ( playGround->noteSequence[playGround->currentNoteIndex] == note.value) {
        // Ăn đúng nốt theo thứ tự
        Uint32 currentTime = SDL_GetTicks();
        Uint32 elapsedTime = currentTime - playGround->getSequenceStartTime();
        if (elapsedTime <= playGround->getSequenceTimeLimit()) {
          // Ăn đúng nốt theo thứ tự và trong thời gian cho phép
          playGround->addScore(10);// +10 diem khi an dung not
        audioManager->playNoteChunk(note.value);
            effectManager->createEatEffect(note.position.getx() * CELL_SIZE.width,note.position.gety() * CELL_SIZE.height);
            playGround->setGuiding(false);
        if (playGround->currentNoteIndex >= 4) {
            // Hoàn thành bản nhạc
            playGround->setIsSymphonyMode(true);
            playGround->generateNotes(body);
            //playGround->startSymphonyMode();
            playGround->addScore(50);//cong 50 diem khi hoan thanh chuoi
            //playGround->currentNoteIndex = 0;
            audioManager->playCompleteSong();
            for (size_t i = 0; i < playGround->getNotes().size(); ++i) {
        Note note = (playGround->getNotes())[i];
        if (head.getx() == note.position.getx() && head.gety() == note.position.gety() && note.value == GOLD_NOTE) {
            playGround->incrementGoldNotesEaten();
             playGround->checkSymphonyStatus();
        }
            //playGround->generateNotes(body);
            //playGround->startNewSequence(); // Bắt đầu chuỗi mới
            std::cout << "Hoan thanh ban nhac!" << std::endl;
        }
        }
        else {
            playGround->currentNoteIndex++;
            // Bắt đầu hướng dẫn cho nốt nhạc tiếp theo
            playGround->setGuiding(true);
            playGround->setGuideStartTime(SDL_GetTicks());
            playGround->generateNotes(body);
        }
        }
    else {
        // Ăn đúng nốt nhưng quá thời gian
            reduceSpeed();
            playGround->setGuiding(false);
            playGround->currentNoteIndex = 0;
            audioManager->playFailChunk();
            body.pop_back();
            std::cout << "Qua thoi gian!" << std::endl;
            playGround->generateNotes(body);
                }
           return;
     }
     else {
        // Ăn sai nốt
        reduceSpeed();
        playGround->setGuiding(false);
        playGround->currentNoteIndex = 0;
        audioManager->playFailChunk();
        body.pop_back(); // Không làm rắn dài ra
        std::cout << "An sai note!" << std::endl;
         playGround->generateNotes(body);
    }
    return;
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

void Snake:: reduceSpeed() {
        speed = max(MIN_SPEED, speed * 0.8f); // Giảm 20%
        pennaltyTimer = 50; // 5 giây (giả sử 60 FPS)
    }

void Snake::update() {
        if (pennaltyTimer > 0) {
            pennaltyTimer--;
            if (pennaltyTimer == 0) speed = 1.0f; // Khôi phục tốc độ
        }
    }

float Snake::getSpeed() const { return speed; }

void Snake::restoreSpeed() {
    speed = 1.0f; // Hồi phục tốc độ về giá trị ban đầu
    pennaltyTimer = 0; // Reset penaltyTimer
    std::cout << "Speed restored to 1.0!" << std::endl; // Debug
}

