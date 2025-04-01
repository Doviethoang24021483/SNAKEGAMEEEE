
#include<SDL.h>
#include "SDL_utils.h"
#include<iostream>

 void logSDLError(std::ostream& os,
const std::string &msg, bool fatal = false)
 {
    os << msg << " Error: " << SDL_GetError() << std::endl;
if (fatal) {
        SDL_Quit();
        exit(1);
    }
 }
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
 if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
 logSDLError(std::cout, "SDL_Init", true);

 window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
                           SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
  if(window==nullptr) logSDLError(std::cout, "CreateWindow", true);
  renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC) ;
  if (renderer==nullptr) logSDLError(std::cout, "CreateRenderer", true);

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"nearest");
  SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
    SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
    if (texture == nullptr){
        logSDLError(std::cout, "IMG_LoadTexture");
    }
    return texture;
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* snakeTexture, SDL_Texture* snakeHeadTexture,SDL_Texture* cherryTexture,SDL_Texture* wallTexture,SDL_Texture* backgroundTexture, SDL_Texture* splashScreen, SDL_Texture* noteTargetTexture,SDL_Texture* goldNoteTexture) {
     SDL_DestroyTexture(snakeTexture);
    SDL_DestroyTexture(snakeHeadTexture);
    SDL_DestroyTexture(cherryTexture);
    SDL_DestroyTexture(wallTexture);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(splashScreen);
    SDL_DestroyTexture(noteTargetTexture);
    SDL_DestroyTexture(goldNoteTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while(true){
        if(SDL_WaitEvent(&e)!=0&&(e.type==SDL_KEYDOWN||e.type==SDL_QUIT))
            return;
        SDL_Delay(100);
    }
}
