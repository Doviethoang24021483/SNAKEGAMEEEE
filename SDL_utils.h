#ifndef SDL_UTILS_H
#define SDL_UTILS_H


#include <SDL.h>
#include<SDL_image.h>
#include<string>
using namespace std;

void logSDLError(std::ostream& os,
const std::string &msg, bool fatal);
const int SCREEN_WIDTH = 800;
 const int SCREEN_HEIGHT = 600;
 const string WINDOW_TITLE =
"An Implementation of Code.org Painter";
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
 void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
 void waitUntilKeyPressed();
#endif // SDL_UTILS_H

