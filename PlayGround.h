
#ifndef PLAYGROUND_H // Kiem tra PLAYGROUND_H dinh nghia chua
#define PLAYGROUND_H // Dinh nghia va nap noi dung file
#include<iostream>
#include<vector>
using namespace std;
// Tao ra cac hang so dai dien cho cac loai o trong san
enum CellType{
  CELL_EMPTY,
  CELL_SNAKE, // Tu dong tang 1
  CELL_CHERRY // Tu dong tang 2
};

enum GameStatus {
   GAME_RUNNING ,
   GAME_WON,
   GAME_LOST
};
// Vi tri tren san cho phep de dang truy cap tu ben ngoai
struct Position
{
  int x,y;
  Position(int x_=0, int y_=0){
     x=x_;
     y=y_;
  }
  bool isInsideBox(int left, int top, int w, int h ) const {
   return (x>= left && x<left+w && y >= top);
 }
};
class PlayGround{
    private: // Khong the truy cap tu ben ngoai
  vector<vector<CellType>> squares; // Mang 2 chieu luu trang thai cac o
  int score; // Diem so
  GameStatus status;
  bool isStop;
  int width;
  int height;

    //public: // Ham thanh vien cho phep truy cap tu ben ngoai
    // bool isGameRunning() const { return status == GAME_RUNNING;}//Kiem tra game co dang chay hay ko
     // chi co the doc ko the sua doi tuong********
     //void processUserInput(UserInput input) { } // xu li dau vao cua nguoi choi nhu di chuyen ran
     //void nextStep() {} //cap nhat trang thai tro choi trong moi buoc di chuyen, va cham, sinh cherry moi neu can
    // void changeCellState( Position pos, CellType type); // thay doi trang thai cua mot o tren san choi
    public:
    PlayGround(int width, int height);
    int getWidth() const;
    int getHeight() const;
    CellType getCellState(Position pos) const;
    int changeCellState(Position pos, CellType type);
    bool checkPosition(Position pos);
    bool isGameRunning() const;
};
#endif // PLAYGROUND_H giup dong vong ma duoc bao ve
