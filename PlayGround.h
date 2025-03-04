
#ifndef PLAYGROUND_H // Kiem tra PLAYGROUND_H dinh nghia chua
#define PLAYGROUND_H // Dinh nghia va nap noi dung file
#include<iostream>
#include "Snake.h"
#include<vector> // Vi can lam viec voi doi tuong snake
using namespace std;
// Tao ra cac hang so dai dien cho cac loai o trong san
enum CellType{
  CELL_EMPTY = 0,
  CELL_SNAKE, // Tu dong tang 1
  CELL_CHERRY // Tu dong tang 2
};
// Trang thai cua game su dung Bitwise OR
enum GameStatus {
   GAME_RUNNING = 1,
   GAME_STOP = 2,
   GAME_WON = 4 | GAME_STOP, // thang thi dung
   GAME_LOST = 8 | GAME_STOP,// thua thi cung dung
};
// Vi tri tren san cho phep de dang truy cap tu ben ngoai
struct Position
{
  int x,y;
};
class PlayGround{
    private: // Khong the truy cap tu ben ngoai
  vector<vector<CellType>> squares; // Mang 2 chieu luu trang thai cac o
  Snake snake; // Doi tuong ran trong san choi
  int score; // Diem so
  GameStatus status; // Trang thai tro choi
    public: // Ham thanh vien cho phep truy cap tu ben ngoai
     bool isGameRunning() const { return status == GAME_RUNNING;}//Kiem tra game co dang chay hay ko
     // chi co the doc ko the sua doi tuong********
     void processUserInput(UserInput input) { } // xu li dau vao cua nguoi choi nhu di chuyen ran
     void nextStep() {} //cap nhat trang thai tro choi trong moi buoc di chuyen, va cham, sinh cherry moi neu can
     void changeCellState( Position pos, CellType type); // thay doi trang thai cua mot o tren san choithế
};
#endif // PLAYGROUND_H giup dong vong ma duoc bao ve
