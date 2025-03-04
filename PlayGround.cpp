
#include<iostream>
#include "Playground.h"
using namespace std;

//Ham khoi tao dung Member Initialization List
 PlayGround::PlayGround(int width, int height)
 : squares(height, vector<CellType>(width, CELL_EMPTY)) ,// khoi tao mang san choi ban dau co gt empty
   snake(this),// Goi toi ham khoi tao Snake , truyen doi tuong PlayGround hien tai vao

