 #include<iostream>
 #include<SDL.h>
 #include "SDL_utils.h"
 int main(int argc, char* argv[])
 {
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);
 // Your drawing code here
 // use SDL_RenderPresent(renderer) to show it
    waitUntilKeyPressed();
    quitSDL(window, renderer);
 return 0;
 }
