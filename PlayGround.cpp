
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
lastGoldTime(SDL_GetTicks()),//luu thoi diem bat dau game
isGoldTime(false),//ban dau ko o trang thai vang
isGuiding(true),
  guideStartTime(SDL_GetTicks()) // Khởi tạo thời điểm bắt đầu
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

    for (int i = 0; i < NUM_NOTES; ++i) {
        Note newNote;
        bool validPosition = false;
        while (!validPosition) {
            // Generate random position
           int x = rand() % (SCREEN_WIDTH / CELL_SIZE.width);
            int y = rand() % (SCREEN_HEIGHT / CELL_SIZE.height);
            newNote.position = Position(x, y);

            // Check if the position is valid (not overlapping with snake body)
            validPosition = true;
            for (const Position& segment : snakeBody) {
                if (segment.getx() == newNote.position.getx() && segment.gety() == newNote.position.gety()) {
                    validPosition = false;
                    break;
                }
            }
            //Check not trùng với các note khác
           for (const Note& note : notes) {
                if (note.position.getx() == newNote.position.getx() && note.position.gety() == newNote.position.gety()) {
                    validPosition = false;
                    break;
                }
            }

        }
        // Assign note value
        newNote.value = static_cast<NoteValue>(rand() % NUM_NOTE_VALUES);//Chuyen doi so nguyen ngau nhien tu NUM_NOTE_VALUES - 1 thanh 1 gia tri thuoc kieu NoteValue

        notes.push_back(newNote);
    }

    //set target note
        if (!notes.empty()) {
        int randomIndex = rand() % notes.size();
        targetNote = notes[randomIndex]; //Lay random 1 not nhac trong notes lam not muc tieu
    } else {
        // Handle case where no notes were created
        std::cerr << "Warning: No notes were created." << std::endl;
    }
    setGuiding(true); // Set isGuiding to true here
     setGuideStartTime(SDL_GetTicks());
    startNewSequence(); // Bắt đầu đếm thời gian
}

//void PlayGround::removeNote(Position note) {
    //for ( int i = 0; i < notes.size(); ++i) {
       // if (notes[i].getx() == note.getx() && notes[i].gety() == note.gety()) {
           // notes.erase(notes.begin() + i);
            //break;
       // }
  //  }
//}
void PlayGround::removeNote(Note note) {
    for (size_t i = 0; i < notes.size(); ++i) {
        if (notes[i].position.getx() == note.position.getx() && notes[i].position.gety() == note.position.gety()&& notes[i].value == note.value) {
            notes.erase(notes.begin() + i);
            return;
        }
    }
}
bool PlayGround::goldTime(){
  Uint32 currentTime = SDL_GetTicks();

  //Neu da qua 30s thi kich hoat thoi gian vang
  if(currentTime - lastGoldTime >= 30000){
    isGoldTime = true;
    lastGoldTime = currentTime ;// dat lai thoi diem bat dau
  // Sau 10s thi tat thoi gian vang
  if(isGoldTime && (currentTime - lastGoldTime >= 10000)){
    isGoldTime = false;
  }
  }
  return isGoldTime;
}
 //Position PlayGround::getTargetNote(){
  // return targetNote;
 //}
 Note PlayGround::getTargetNote(){
 return targetNote;
 }

NoteValue PlayGround::getNoteSequence(int index) {
    return noteSequence[index];
}
void PlayGround::startNewSequence() {
    sequenceStartTime = SDL_GetTicks();
}
