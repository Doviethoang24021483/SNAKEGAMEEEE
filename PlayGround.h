#ifndef PLAYGROUND_H
#define PLAYGROUND_H
#include  <vector>
#include "Position.h"

//Dinh nghia cac loai o co the co tren san choi
enum CellType{
 CELLEMPTY,
 CELLSNAKE,
 CELLCHERRY
};

//Dinh nghia cac trang thai co the co
enum GameStatus{
 GAMERUNNING,
 GAMEWON,
 GAMELOST,
 GAMESTOP
};
//Kich thuoc o( co the se thay doi)
struct CellSize {
    int width;
    int height;
};

class PlayGround {
private:
 int diemso;
 int width, height; //Kich thuoc san choi
 GameStatus status; //Trang thai game
 std::vector<std::vector<CellType>> squares; //vector 2 chieu luu tru trang thai cua cac o
 std::vector<Position> notes; //Vecto luu tru vi tri cua cac not nhac
 const int NUM_NOTES = 20; //Tong so not nhac
 bool gameRun; //Kiem tra game con chay ko
public:
    PlayGround(int width_=0, int height_=0); // Khoi tao san choi voi kich thuoc mac dinh la 0 0

    int getWidth() const; //Ham tra ve chieu rong san choi
    int getHeight() const; //Ham tra ve chieu dai san choi

    CellType getCellType(Position pos); // Ham tra ve trang thai cua 1 o tai vi tri xd
    CellType changeCellType(CellType type, Position pos ); // Ham thay doi trang thai o tren san choi

    bool isGameRun() const; // Kiem tra game con chay ko
    void stopGame(); // Ham ket thuc game
    void setGameRun(bool run); // Dat lai trang thai chay cua game

    const std::vector<Position>& getNotes() const; // Ham tra ve vi tri cua cac not nhac
    void generateNotes(const std::vector<Position>& snakeBody); // Ham sinh ngau nhien 10 not nhac
    void generateNewNote(const std::vector<Position>& snakeBody);  // Ham sinh ngau nhien not nhac moi
    void removeNote(Position note); // Xoa not nhac
};
#endif // PLAYGROUND_H

