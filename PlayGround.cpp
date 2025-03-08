
#include<iostream>
#include "Playground.h"
#include<cassert>
#include<vector>
using namespace std;

 PlayGround::PlayGround(int width, int height)
  :width(width),
  height (height),
   squares (height,vector<CellType>(width, CELL_EMPTY)),
    status(GAME_RUNNING),
    isStop (false)
            {
            }
 int PlayGround::getWidth() const{
  return squares[0].size();
 }
 int PlayGround::getHeight() const{
  return squares.size();
 }

 CellType PlayGround::getCellState(Position pos) const{
   assert(pos.isInsideBox(0,0,getWidth(),getHeight()));
   return squares[pos.y][pos.x];
 }
 int PlayGround::changeCellState(Position pos, CellType type){
  assert(pos.isInsideBox(0,0,getWidth(),getHeight()));
  return squares[pos.y][pos.x]=type;
 }
 bool PlayGround::checkPosition(Position pos){
  if(!pos.isInsideBox(0,0,getWidth(),getHeight()))
    return false;
  return true;
 }
 bool PlayGround::isGameRunning() const{
   return status == GAME_RUNNING && !isStop;
 }
