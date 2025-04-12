
#include<iostream>
#include "PlayGround.h"
#include "Position.h"
#include<cassert>
#include<vector>
#include<cstdlib>
#include<ctime>
#include"SDL_utils.h"
#include"EffectManager.h"
#include "Renderer.h"
using namespace std;

const CellSize CELL_SIZE = {30,30};

// Ham khoi tao
PlayGround::PlayGround(int width_, int height_)
: width(width_),height(height_),
  squares(height,vector<CellType>(width,CELLEMPTY)),//initializer list toi uu
  status(GAMERUNNING),
  gameRun(true),
  isGuiding(true),
  guideStartTime(SDL_GetTicks()) // Khởi tạo thời điểm bắt đầu
  ,score(0)
{
 srand(time(0));                 // Tao ra cac rand khac nhau
 generateNotes({});              // Tao ra danh sach cac not nhac ban dau trong tro choi chua can quan tam den vi tri ran
}

int PlayGround::getWidth() const {
    return width;
}

int PlayGround::getHeight() const{
    return height;
}

CellType PlayGround::getCellType(Position pos)
{
   assert(pos.isInsideBox(0,0,getWidth(),getHeight())); //Dam bao pos hop le nam trong san choi
   return squares[pos.gety()][pos.getx()];
}

CellType PlayGround::changeCellType(CellType type, Position pos){
    if(pos.isInsideBox(0,0,getWidth(),getHeight()))
    squares[pos.gety()][pos.getx()]=type;
    return squares[pos.gety()][pos.getx()];
}


bool PlayGround::isGameRun()const{
 return status == GAMERUNNING && gameRun;
}

void PlayGround::stopGame(){
 gameRun = false;
 status = GAMESTOP;
 cout<<"gameover"<<endl;
}

void PlayGround::setGameRun(bool run){
  gameRun=run;
}


const std::vector<Note>& PlayGround::getNotes() const {
    return notes;
}


void PlayGround::generateNotes(const std::vector<Position>& snakeBody) {
    notes.clear();                // Xóa các nốt nhạc cũ
   if (isSymphonyMode == true) {  //Kiem tra xem co o trang thai giao huong hay ko
    for (int i = 0; i < GOLD_NOTES_REQUIRED; i++) {   //Duyet qua so lan bang so not nhac can an trong symphony
        Note newNote;                                 //Tao ra 1 note moi
        bool validPosition = false;                   //Ban dau cho vi tri la chua hop li
        while (!validPosition) {
            int x = rand() % (SCREEN_WIDTH / CELL_SIZE.width);
            // Tao vi tri ngau nhien cho cac not nhac dam bao cac not nhac chi xuat hien trong khu vuc choi duoc , tranh vung UI
            int playableHeightInCells = (SCREEN_HEIGHT - GAME_AREA_OFFSET_Y) / CELL_SIZE.height;  //Khu vuc choi duoc co bao nhieu o theo chieu doc
            int offsetYInCells = GAME_AREA_OFFSET_Y/CELL_SIZE.height; // Lam tron len vi day la phan UI neu ko lam tron len thi khi tao not nhac co the se bi dinh vao phan du cua UI do
            int y = (rand() % playableHeightInCells) + offsetYInCells;
            newNote.position = Position(x, y);
            validPosition = true;
            for (const Position& segment : snakeBody) {
                if (segment.getx() == newNote.position.getx() && segment.gety() == newNote.position.gety()) {
                    validPosition = false;
                    break;
                }
            }
            for (const Note& note : notes) {
                if (note.position.getx() == newNote.position.getx() && note.position.gety() == newNote.position.gety()) {
                    validPosition = false;
                    break;
                }
            }
            newNote.value = GOLD_NOTE;
        }
        notes.push_back(newNote);
    }
}
        else {
    for (int i = 0; i < NUM_NOTES; ++i) {
        Note newNote;
        bool validPosition = false;
        while (!validPosition) {
            int x = rand() % (SCREEN_WIDTH / CELL_SIZE.width);
            // Sửa lại tọa độ y để không nằm trong vùng UI
            int playableHeightInCells = (SCREEN_HEIGHT - GAME_AREA_OFFSET_Y) / CELL_SIZE.height;
            int offsetYInCells = GAME_AREA_OFFSET_Y/CELL_SIZE.height;// Làm tròn lên để bắt đầu từ ô đầu tiên dưới vùng UI
            int y = (rand() % playableHeightInCells) + offsetYInCells;
            newNote.position = Position(x, y);
            validPosition = true;
            for (const Position& segment : snakeBody) {
                if (segment.getx() == newNote.position.getx() && segment.gety() == newNote.position.gety()) {
                    validPosition = false;
                    break;
                }
            }
            for (const Note& note : notes) {
                if (note.position.getx() == newNote.position.getx() && note.position.gety() == newNote.position.gety()) {
                    validPosition = false;
                    break;
                }
            }
        }
        newNote.value = static_cast<NoteValue>(rand() % 5); // Chuyen kieu so nguyen ve kieu NoteValue
        notes.push_back(newNote);
    }
        if (!notes.empty()) {        //Thuc ra ko co truong hop note trong
        int randomIndex = rand() % notes.size();
        targetNote = notes[randomIndex]; //Lay random 1 not nhac trong notes lam not muc tieu
    }   else {
           std::cerr << "Warning: No notes were created." << std::endl;
       }
       }
    //setGuiding(true);                       //Xem lai boi khi khoi tao da gan setGuiding la true
    //setGuideStartTime(SDL_GetTicks());      // Da khoi tao rui lieu co can set nx ko
    startNewSequence();                     // Bắt đầu đếm thời gian de tinh xem an not nhac goi la dung hay ko
}

void PlayGround::removeNote(Note note) {
    for (int i = 0; i < notes.size(); ++i) {
        if (notes[i].position.getx() == note.position.getx() && notes[i].position.gety() == note.position.gety()&& notes[i].value == note.value) {
            notes.erase(notes.begin() + i);
            return;
        }
    }
}

Note PlayGround::getTargetNote(){
 return targetNote;
 }

NoteValue PlayGround::getNoteSequence(int index) {       //Lay gia tri not nhac trong chuoi nhac
    return noteSequence[index];
}

void PlayGround::startNewSequence() {                    //Tinh thoi gian de ran an not goi la dung
    sequenceStartTime = SDL_GetTicks();
}

void PlayGround::startSymphonyMode() {
    isSymphonyMode = true;
    symphonyStartTime = SDL_GetTicks();
    goldNotesEaten = 0;
    notes.clear(); // Xóa các nốt cũ
    std::cout << "Started Symphony Mode! Collect 20 gold notes in 50 seconds!" << std::endl;
}

void PlayGround::endSymphonyMode() {         ///Kiem tra lai ham end
    isSymphonyMode = false;
    goldNotesEaten = 0;
    notes.clear();
    startNewSequence();
    std::cout << "Symphony Mode ended! Returning to normal mode." << std::endl;
}

void PlayGround::checkSymphonyStatus() {
    if (!isSymphonyMode) return;

    Uint32 currentTime = SDL_GetTicks();
    Uint32 elapsedTime = currentTime - symphonyStartTime;   //Thoi gian da troi qua
    if (elapsedTime <= SYMPHONY_TIME_LIMIT && goldNotesEaten >= GOLD_NOTES_REQUIRED) { // chua het thoi gian da an het note vang
    isSymphonyMode = false;
    addScore(200);
    gameRun = false;
    std::cout << "YOU WIN" << std::endl;
    bool playAgain = rendererkk->showMessage("YOU WIN", {0, 255, 0, 255});
    stopGame();
    if (playAgain) {
        reset();
        // Rắn sẽ được reset trong main.cpp
    } else {
        gameRun = false; // Đảm bảo thoát game nếu không chơi lại
    }
}   else if( elapsedTime > SYMPHONY_TIME_LIMIT && goldNotesEaten < GOLD_NOTES_REQUIRED){
        reset();
}
}
void PlayGround::reset() {
    // Reset trạng thái game
    status = GAMERUNNING;
    gameRun = true;
    isSymphonyMode = false;
    goldNotesEaten = 0;
    score = 0; // Reset điểm số
    currentNoteIndex = 0;
    notes.clear();
    setGuiding(true);
    setGuideStartTime(SDL_GetTicks());
    startNewSequence();
    generateNotes({}); // Tạo lại các nốt thông thường
}
