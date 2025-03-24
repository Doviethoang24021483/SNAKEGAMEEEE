
#include<iostream>
#include "PlayGround.h"
#include "Position.h"
#include<cassert>
#include<vector>
#include<cstdlib>
#include<ctime>
using namespace std;

// Ham khoi tao
PlayGround::PlayGround(int width_, int height_)
: width(width_),height(height_),
squares(height,vector<CellType>(width,CELLEMPTY)),
status(GAMERUNNING),
gameRun(true)
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


const std::vector<Position>& PlayGround::getNotes() const {
    return notes;
}

void PlayGround::generateNewNote(const vector<Position>& snakeBody) {
    Position newNote;
    bool validPosition = false;
    int maxIterations = 1000; // Chống vòng lặp vô hạn
    while (!validPosition) {
          int x = (rand() % getWidth());
        int y = (rand() % getHeight()) ;
        newNote = Position(x, y);
        validPosition = true;

        // Kiểm tra không trùng với thân rắn
        for (const Position& segment : snakeBody) {
            if (segment.getx() == newNote.getx() && segment.gety() == newNote.gety()) {
                validPosition = false;
                break;
            }
        }
         if (!validPosition) continue; // Bỏ qua các kiểm tra khác nếu đã không hợp lệ

        // Kiểm tra không trùng với các nốt nhạc khác
        for (const Position& note : notes) {
            if (note.getx() == newNote.getx() && note.gety() == newNote.gety()) {
                validPosition = false;
                break;
            }
        }

        if (!validPosition) continue; // Bỏ qua các kiểm tra khác nếu đã không hợp lệ
    }
    // Nếu tất cả các kiểm tra đều vượt qua, vị trí này hợp lệ
        if (validPosition) {
            notes.push_back(newNote);
            return; // Thoát khỏi hàm sau khi tìm thấy một vị trí hợp lệ
        }
         cerr << "Cảnh báo: Không thể tìm thấy vị trí hợp lệ cho nốt nhạc sau " << maxIterations << " lần thử." << endl;
    }

void PlayGround::generateNotes(const vector<Position>& snakeBody) {
    notes.clear(); // Xóa các nốt nhạc cũ (nếu có)
    for (int i = 0; i < NUM_NOTES; ++i) {
        generateNewNote(snakeBody);
    }
}


void PlayGround::removeNote(Position note) {
    for ( int i = 0; i < notes.size(); ++i) {
        if (notes[i].getx() == note.getx() && notes[i].gety() == note.gety()) {
            notes.erase(notes.begin() + i);
            break;
        }
    }
}
