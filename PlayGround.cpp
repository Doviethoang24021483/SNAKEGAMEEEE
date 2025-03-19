
#include<iostream>
#include "PlayGround.h"
#include "Position.h"
#include<cassert>
#include<vector>
#include<cstdlib>
#include<ctime>
using namespace std;

PlayGround::PlayGround(int width_, int height_)
: width(width_),height(height_),
squares(height,vector<CellType>(width,CELLEMPTY)),
status(GAMERUNNING),
gameRun(true)
//notes(0,0)
{
 srand(time(0));
 //generateCherry({}); //tao vi tri ngau nhien
 generateNotes({}); // Thêm dòng này
 //addWall(0, 5);
  //  addWall(0 , 4);
  //  addWall(0, 0);
   // addWall(0 , 2);
   // addWall(0, 3);
   // addWall(0, 1);
   // addWall(5,0);addWall(5,1);addWall(5,2);addWall(5,3);addWall(5,4);
   // addWall(9,0);addWall(9,1);addWall(9,2);addWall(9,3);addWall(9,4);
   // addWall(8,4);addWall(8,3); addWall(15,15);addWall(15,16); addWall(18,14);
   // addWall(17,13);
    //addWall(5,18);
}
//Tao ra vi tri cherry ngau nhien
//void PlayGround::generateCherry(const vector<Position>& snakeBody) {
 //Position newCherry;
 //bool validPosition = false;
 //while(!validPosition){
   // int x = rand() % getWidth();
    //int y = rand() % getHeight();
    //newCherry=Position(x,y);
    //validPosition=true;
    //for(const Position& segment: snakeBody){
       // if(segment.getx() == newCherry.getx() && segment.gety()==newCherry.gety()){
          //  validPosition = false;
          //  break;
        //}
    //}
    //for(const Position& segment: walls){
     //   if(segment.getx() == newCherry.getx() && segment.gety()==newCherry.gety()){
       //     validPosition = false;
          //  break;
       // }
   // }
// }
 //setCherry(newCherry);
//}

int PlayGround::getWidth() const {
    return width;
}

int PlayGround::getHeight() const{
    return height;
}

//Position PlayGround::getCherry() const{
  // return cherry;
//}

CellType PlayGround::getCellType(Position pos)
{ assert(pos.isInsideBox(0,0,getWidth(),getHeight()));
return squares[pos.gety()][pos.getx()];
}

CellType PlayGround::changeCellType(CellType type, Position pos){
    if(pos.isInsideBox(0,0,getWidth(),getHeight()))
    squares[pos.getx()][pos.gety()]=type;
    return squares[pos.gety()][pos.getx()];
}

bool PlayGround::isGameRun()const{
 return status == GAMERUNNING && gameRun;
}

//void PlayGround::setCherry(Position newCherry){
 // cherry=newCherry;
//}
const std::vector<Position>& PlayGround::getNotes() const { // Thêm hàm này
    return notes;
}
void PlayGround::stopGame(){
 gameRun = false;
 status = GAMESTOP;
 cout<<"gameover"<<endl;
}

void PlayGround::setGameRun(bool run){
  gameRun=run;
}
//const std::vector<Position>& PlayGround::getWalls() const {
  //  return walls;
//}

//void PlayGround::addWall(int x, int y) {
   // Position newWall(x, y);
   // walls.push_back(newWall);
   // changeCellType(CELLWALL, newWall);
//}
void PlayGround::generateNotes(const vector<Position>& snakeBody) {
    notes.clear(); // Xóa các nốt nhạc cũ (nếu có)
    for (int i = 0; i < NUM_NOTES; ++i) {
        generateNewNote(snakeBody);
    }
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
       // if (!validPosition) continue; // Bỏ qua kiểm tra tường và các kiểm tra khác nếu đã không hợp lệ

        // Kiểm tra không trùng với tường
       // for (const Position& wall: walls) {
          //  if (wall.getx() == newNote.getx() && wall.gety() == newNote.gety()) {
              //  validPosition = false;
              //  break;
           // }
        //}
         if (!validPosition) continue; // Bỏ qua các kiểm tra khác nếu đã không hợp lệ
        // Kiểm tra không trùng với các nốt nhạc khác
        for (const Position& note : notes) {
            if (note.getx() == newNote.getx() && note.gety() == newNote.gety()) {
                validPosition = false;
                break;
            }
        }
    }


    // Nếu tất cả các kiểm tra đều vượt qua, vị trí này hợp lệ
        if (validPosition) {
            notes.push_back(newNote);
            return; // Thoát khỏi hàm sau khi tìm thấy một vị trí hợp lệ
        }
         cerr << "Cảnh báo: Không thể tìm thấy vị trí hợp lệ cho nốt nhạc sau " << maxIterations << " lần thử." << endl;
    }

// Thêm hàm này
void PlayGround::removeNote(Position note) {
    for (size_t i = 0; i < notes.size(); ++i) {
        if (notes[i].getx() == note.getx() && notes[i].gety() == note.gety()) {
            notes.erase(notes.begin() + i);
            break;
        }
    }
}
