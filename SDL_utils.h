
#ifndef SDL_UTILS_H
#define SDL_UTILS_H


#include <SDL.h>
#include <SDL_image.h>
#include<string>


void logSDLError(std::ostream& os,const std::string &msg, bool fatal);
const int SCREEN_WIDTH = 600 ;
 const int SCREEN_HEIGHT = 600;
 // Trong main.cpp hoặc SDL_utils.h
const int UI_HEIGHT = 29; // Chiều cao của vùng UI (phía trên)
const int GAME_AREA_OFFSET_Y = UI_HEIGHT; // Dịch chuyển khu vực chơi game xuống
 const std:: string WINDOW_TITLE =
"An Implementation of Code.org Painter";
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* snakeTexture, SDL_Texture* snakeHeadTexture, SDL_Texture* cherryTexture, SDL_Texture* wallTexture,SDL_Texture* backgroundTexture,
             SDL_Texture* slashScreen, SDL_Texture* noteTargetTexture,SDL_Texture* goldNoteTexture);
 void waitUntilKeyPressed();
#endif // SDL_UTILS_H

