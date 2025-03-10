#include<SDL.h>
#include<iostream>
#include "Position.h"
#include "PlayGround.h"
#include "SDL_utils.h"
#include "Snake.h"
using namespace std;
const int CELL_SIZE = 30;//Kich thuoc moi o vuong
//Ham ve nen mau tim va cac o vuong mau trang
void drawGrid(SDL_Renderer* renderer){
  //dat mau nen tim
  SDL_SetRenderDrawColor(renderer,128,0,128,255);
  // ve mau tim len toan man hinh
  SDL_RenderClear(renderer);
  // dat mau cho o vuong
  SDL_SetRenderDrawColor(renderer,255,255,255,255);
  //ve cac o vuong theo luoi
  for( int x = 0; x < SCREEN_WIDTH; x+=CELL_SIZE){
    for(int y = 0 ; y < SCREEN_HEIGHT; y+=CELL_SIZE){
        //Dinh nghia o vuong sap duoc ve
        SDL_Rect cell = {x,y,CELL_SIZE,CELL_SIZE};
        //ve duong vien hinh vuong
        SDL_RenderDrawRect(renderer,&cell);
    }
  }
  SDL_RenderPresent(renderer);
}
void drawSnake(SDL_Renderer* renderer, int x, int y){
 SDL_SetRenderDrawColor(renderer,255,0,0,255);//mau do
 SDL_Rect rect = { x, y, CELL_SIZE,CELL_SIZE};
 //Ve hinh tron
 for ( int i = 0 ; i < CELL_SIZE; i++){
    for ( int j = 0 ; j < CELL_SIZE; j++)
    {
        int dx= CELL_SIZE/2 - i;
        int dy= CELL_SIZE/2- j;
        if((dx*dx + dy*dy)<=(CELL_SIZE/2)*((CELL_SIZE/2))){
            SDL_RenderDrawPoint(renderer,x+i,y+j);
        }
    }
 }
}
void drawCherry(SDL_Renderer* renderer, int x, int y){
    SDL_SetRenderDrawColor(renderer,255,165,0,255);
    SDL_Rect rect={x,y,CELL_SIZE,CELL_SIZE};
    SDL_RenderFillRect(renderer,&rect);
}
void renderGame(SDL_Renderer* renderer, Snake* snake,PlayGround* playGround)
{ drawGrid(renderer);
 Position snakePos = snake->getPosition();
 Position cherryPos= playGround->getCherry();
 Direction direction= snake->getDirection();
 int snakeX=(snakePos.getx())*CELL_SIZE;
 int snakeY=snakePos.gety()*CELL_SIZE;
 int cherryX=cherryPos.getx()*CELL_SIZE;
 int cherryY=cherryPos.gety()*CELL_SIZE;
drawSnake(renderer,snakeX, snakeY);
drawCherry(renderer,cherryX,cherryY);
SDL_RenderPresent(renderer);
}
//Ham chuyen su kiên SDL thanh Userinput
UserInput getUserInputFromEvent(SDL_Event* event)
{

}
int main(int argc,char *argv[]){

 //PlayGround pr(20,20);
 //Position posCherry=pr.getCherry();
 //Snake snake (&pr);
 //Position possnake= snake.getPosition();
 //pr.changeCellType(CELLSNAKE,snake.getPosition());
 //for(int i = 0 ; i < pr.getWidth() ; i++)
 //{

    // for ( int  j = 0 ; j < pr.getHeight(); j++)
     //{  if(i==posCherry.getx()&&j==posCherry.gety())
     //{
     //    cout<<pr.changeCellType(CELLCHERRY,posCherry)<<" ";
     //}
     //  else{ Position pos(i,j);
     //   cout<<pr.getCellType(pos)<<" ";}
     //}
     //cout<<endl;
 //}
SDL_Window* window;
SDL_Renderer* renderer;
PlayGround playGround(20,20);
Snake snake(&playGround);
initSDL(window,renderer);
Direction direction = snake.getDirection();
renderGame(renderer,&snake,&playGround);
waitUntilKeyPressed();
quitSDL(window,renderer);
return 0;
}
