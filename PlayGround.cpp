
#include<iostream>
#include "PlayGround.h"
#include "Position.h"
#include<cassert>
#include<vector>
#include<cstdlib>
#include<ctime>
#include"SDL_utils.h"
#include"EffectManager.h"
using namespace std;
const CellSize CELL_SIZE = {30,30};
// Ham khoi tao
PlayGround::PlayGround(int width_, int height_)
: width(width_),height(height_),
squares(height,vector<CellType>(width,CELLEMPTY)),
status(GAMERUNNING),
gameRun(true),
isGuiding(true),
  guideStartTime(SDL_GetTicks()) // Khởi tạo thời điểm bắt đầu
  , score(0)
{
 srand(time(0)); // Tao ra cac rand khac nhau
 generateNotes({}); // Tao ra danh sach cac not nhac ban dau trong tro choi chua can quan tam den vi tri ran
}

int PlayGround::getWidth() const {
    return width;
}

int PlayGround::getHeight() const{
    return height;
}


CellType PlayGround::getCellType(Position pos)
{
   assert(pos.isInsideBox(0,0,getWidth(),getHeight())); //Dam bao pos hop le
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
    notes.clear(); // Xóa các nốt nhạc cũ
   if (isSymphonyMode == true) {
    for (int i = 0; i < GOLD_NOTES_REQUIRED; i++) {
        Note newNote;
        bool validPosition = false;
        while (!validPosition) {
            int x = rand() % (SCREEN_WIDTH / CELL_SIZE.width);
            // Sửa lại tọa độ y để không nằm trong vùng UI
            int playableHeightInCells = (SCREEN_HEIGHT - GAME_AREA_OFFSET_Y) / CELL_SIZE.height;
            int offsetYInCells = (GAME_AREA_OFFSET_Y + CELL_SIZE.height - 1) / CELL_SIZE.height; // Làm tròn lên để bắt đầu từ ô đầu tiên dưới vùng UI
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
            int offsetYInCells = (GAME_AREA_OFFSET_Y + CELL_SIZE.height - 1) / CELL_SIZE.height; // Làm tròn lên để bắt đầu từ ô đầu tiên dưới vùng UI
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
        newNote.value = static_cast<NoteValue>(rand() % 5);
        notes.push_back(newNote);
    }
}
        if (!notes.empty()) {
        int randomIndex = rand() % notes.size();
        targetNote = notes[randomIndex]; //Lay random 1 not nhac trong notes lam not muc tieu
    }   else {
           std::cerr << "Warning: No notes were created." << std::endl;
       }
    setGuiding(true);
    setGuideStartTime(SDL_GetTicks());
    startNewSequence(); // Bắt đầu đếm thời gian
        }

void PlayGround::removeNote(Note note) {
    for (size_t i = 0; i < notes.size(); ++i) {
        if (notes[i].position.getx() == note.position.getx() && notes[i].position.gety() == note.position.gety()&& notes[i].value == note.value) {
            notes.erase(notes.begin() + i);
            return;
        }
    }
}

Note PlayGround::getTargetNote(){
 return targetNote;
 }

NoteValue PlayGround::getNoteSequence(int index) {
    return noteSequence[index];
}

void PlayGround::startNewSequence() {
    sequenceStartTime = SDL_GetTicks();
}

void PlayGround::startSymphonyMode() {
    isSymphonyMode = true;
    symphonyStartTime = SDL_GetTicks();
    goldNotesEaten = 0;
    notes.clear(); // Xóa các nốt cũ
    //generateNotes(); // Tạo 20 nốt vàng (truyền snakeBody rỗng tạm thời, sẽ cập nhật sau)
    std::cout << "Started Symphony Mode! Collect 20 gold notes in 50 seconds!" << std::endl;
}

void PlayGround::endSymphonyMode() {
    isSymphonyMode = false;
    goldNotesEaten = 0;
    notes.clear();
    startNewSequence();
    std::cout << "Symphony Mode ended! Returning to normal mode." << std::endl;
}

void PlayGround::checkSymphonyStatus() {
    if (!isSymphonyMode) return;

    Uint32 currentTime = SDL_GetTicks();
    Uint32 elapsedTime = currentTime - symphonyStartTime;
    if (elapsedTime <= SYMPHONY_TIME_LIMIT && goldNotesEaten >= GOLD_NOTES_REQUIRED) {
        isSymphonyMode = false;
        addScore(500);
        gameRun = false;
        std::cout << "YOU WIN" << std::endl;
        stopGame();
    } else if (elapsedTime >= SYMPHONY_TIME_LIMIT || notes.empty()) { // Thêm điều kiện notes.empty()
        isSymphonyMode = false;
        goldNotesEaten = 0;
        notes.clear();
        startNewSequence();
        generateNotes({}); // Tạo lại các nốt thông thường
        std::cout << "Symphony Mode ended! Returning to normal mode." << std::endl;
    }
}
