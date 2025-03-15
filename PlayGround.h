#ifndef PLAYGROUND_H
#define PLAYGROUND_H
#include<vector>
#include "Position.h"
using namespace std;
//Dinh nghia cac loai o co the co tren san choi
enum CellType{
 CELLEMPTY,
 CELLSNAKE,
 CELLCHERRY,
 CELLWALL
};
//Dinh nghia cac trang thai co the co
enum GameStatus{
 GAMERUNNING,
 GAMEWON,
 GAMELOST,
 GAMESTOP
};
class PlayGround {
private:
 int diemso;
 int width, height;
 GameStatus status;
 vector<vector<CellType>> squares;
 Position cherry;
 bool gameRun;
 vector<Position> walls;//Danh sach vi tri cac buc tuong
public:
    PlayGround(int width_=0, int height_=0);
    int getWidth() const;
    int getHeight() const;
    Position getCherry() const;
    void setCherry(Position newCherry);
    CellType getCellType(Position pos);
    CellType changeCellType(CellType type, Position pos );
    bool isGameRun() const;
    void generateCherry(const vector<Position>& snakeBody);
    void stopGame();
    void setGameRun(bool run);
    const vector<Position>& getWalls() const;
    void addWall(int x, int y);
};
#endif // PLAYGROUND_H

