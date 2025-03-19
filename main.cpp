#include <SDL.h>
#include <iostream>
#include "Position.h"
#include "PlayGround.h"
#include "SDL_utils.h"
#include "Snake.h"
#include <vector>
#include "AudioManager.h"

const CellSize CELL_SIZE = {24,24}; //Kich thuoc o

//Ham ve nen mau tim va cac o vuong mau trang
void drawBackground(SDL_Renderer* renderer, int cellWidth, int cellHeight, SDL_Texture* backgroundTexture) {
    SDL_Rect destRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &destRect);
}

void drawSnakeSegment(SDL_Renderer* renderer, int x, int y, int width, int height, SDL_Texture* texture,double angle) {
    SDL_Rect destRect = { x, y, width, height };
     SDL_Point center = { width / 2, height / 2 }; // center
    SDL_RenderCopyEx(renderer, texture, NULL, &destRect, angle, &center, SDL_FLIP_NONE);
}
void drawSnakeHead(SDL_Renderer* renderer, int x, int y, int width, int height, SDL_Texture* texture, double angle) {
    SDL_Rect destRect = { x, y, width, height };
    SDL_Point center = { width / 2, height / 2 }; // Rotation center
    SDL_RenderCopyEx(renderer, texture, NULL, &destRect, angle, &center, SDL_FLIP_NONE);
}

//void drawCherry(SDL_Renderer* renderer, int x, int y, int width, int height,SDL_Texture* cherryTexture) {
  //  SDL_Rect desrect = { x, y, width, height };
   // SDL_RenderCopy(renderer, cherryTexture,NULL, &desrect);
//}
void drawNote(SDL_Renderer* renderer, int x, int y, int width, int height,SDL_Texture* noteTexture) { //thay doi ham nay
    SDL_Rect desrect = { x, y, width, height };
    SDL_RenderCopy(renderer, noteTexture,NULL, &desrect);
}
void drawWall(SDL_Renderer* renderer, int x, int y, int width, int height, SDL_Texture* wallTexture) {
    SDL_Rect destRect = { x, y, width, height };
    SDL_RenderCopy(renderer, wallTexture, NULL, &destRect);
}

void renderGame(SDL_Renderer* renderer, Snake* snake, PlayGround* playGround, SDL_Texture* snakeTexture, SDL_Texture* snakeHeadTexture, SDL_Texture* noteTexture,SDL_Texture* wallTexture, SDL_Texture* backgroundTexture) { //thay doi tham so
    drawBackground(renderer, CELL_SIZE.width, CELL_SIZE.height,backgroundTexture);
   // Position cherryPos = playGround->getCherry(); //thay doi doan nay
   // int cherryX = cherryPos.getx() * CELL_SIZE.width;
   // int cherryY = cherryPos.gety() * CELL_SIZE.height;
   // drawCherry(renderer, cherryX, cherryY, CELL_SIZE.width, CELL_SIZE.height,cherryTexture);
     const vector<Position>& notes = playGround->getNotes();
    for (const Position& note : notes) {
        int noteX = note.getx() * CELL_SIZE.width;
        int noteY = note.gety() * CELL_SIZE.height;
        drawNote(renderer, noteX, noteY, CELL_SIZE.width, CELL_SIZE.height, noteTexture);
    }

    const std::vector<Position>& snakeBody = snake->getBody();
    if (!snakeBody.empty()) {
        int headX = snakeBody[0].getx() * CELL_SIZE.width;
        int headY = snakeBody[0].gety() * CELL_SIZE.height;
       double angle = snake->getRotationAngle();
        drawSnakeHead(renderer, headX, headY, CELL_SIZE.width, CELL_SIZE.height, snakeHeadTexture, angle);
    }

    for (size_t i = 1; i < snakeBody.size(); ++i) {
        int snakeX = snakeBody[i].getx() * CELL_SIZE.width;
        int snakeY = snakeBody[i].gety() * CELL_SIZE.height;
        double angle = snake->getRotationAngle();
        drawSnakeSegment(renderer, snakeX, snakeY, CELL_SIZE.width, CELL_SIZE.height, snakeTexture,angle);
    }


    // Vẽ các bức tường
 //   const vector<Position>& walls = playGround->getWalls();
  //  for (const Position& wall : walls) {
     //   int wallX = wall.getx() * CELL_SIZE.width;
      //  int wallY = wall.gety() * CELL_SIZE.height;
      //  drawWall(renderer, wallX, wallY, CELL_SIZE.width, CELL_SIZE.height, wallTexture);
    //}
    //SDL_RenderPresent(renderer);
}

UserInput getUserInputFromEvent(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym)
        {
        case SDLK_UP: return UserInput::KEY_UP;
        case SDLK_DOWN: return UserInput::KEY_DOWN;
        case SDLK_LEFT: return UserInput::KEY_LEFT;
        case SDLK_RIGHT: return UserInput::KEY_RIGHT;

        }
    }
    return UserInput::NO_INPUT;
}

//bool checkSnakeEatCherry(PlayGround* playGround, Snake* snake) {
  //  Position snakeHead = snake->getBody().front();
   // Position cherryPos = playGround->getCherry();
   // if (snakeHead.getx() == cherryPos.getx() && snakeHead.gety() == cherryPos.gety()) {
    //    return true;
    //}
    //return false;
//}
 bool checkSnakeEatNote(PlayGround* playGround, Snake* snake) { //thay doi ham nay
    Position snakeHead = snake->getBody().front();
    const vector<Position>& notes = playGround->getNotes();
    for (const Position& note : notes) {
        if (snakeHead.getx() == note.getx() && snakeHead.gety() == note.gety()) {
            return true;
        }
    }
    return false;
}
int main(int argc, char* argv[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* snakeTexture = nullptr;
    SDL_Texture* snakeHeadTexture = nullptr;
    //SDL_Texture* cherryTexture = nullptr;
    SDL_Texture* noteTexture = nullptr; //thay doi
    SDL_Texture* wallTexture = nullptr;
    SDL_Texture* backgroundTexture = nullptr;
    initSDL(window, renderer);
    AudioManager audioManager;
    if (!audioManager.loadMusic("music.mp3")) {
        std::cerr << "Failed to load music!" << std::endl;
        quitSDL(window, renderer, snakeTexture, snakeHeadTexture, noteTexture, wallTexture, backgroundTexture);
        return -1;
    }
    std::vector<std::string> noteFiles = {
        "a.mp3",   // Ví dụ: nốt C4
        "b.mp3",   // Ví dụ: nốt D4
        "c.mp3",   // Ví dụ: nốt E4
        "d.mp3",   // Ví dụ: nốt F4
        "e.mp3" ,
        "f.mp3",
        "g.mp3"   // Ví dụ: nốt G4
    };
     if (!audioManager.loadNoteChunks(noteFiles)) {
        std::cerr << "Failed to load note chunks!" << std::endl;
        quitSDL(window, renderer, snakeTexture, snakeHeadTexture, noteTexture, wallTexture, backgroundTexture);
        return -1;
    }
     audioManager.setMusicVolume(30);
     audioManager.playMusic(); // Phát nhạc khi game bắt đầu
      PlayGround playGround(20, 20);
       Snake snake(&playGround, &audioManager); // Truyền audioManager vào Snake
    // Đảm bảo rằng tên file ảnh là chính xác và các file ảnh nằm trong cùng thư mục với main.cpp
    snakeTexture = loadTexture("snake_body.png", renderer);
     noteTexture = loadTexture("cherry.png", renderer); //thay doi;
    snakeHeadTexture = loadTexture("snake_head.png", renderer);
    wallTexture = loadTexture("wall.png",renderer);
     backgroundTexture = loadTexture("background.png", renderer);
    if (snakeTexture == nullptr || snakeHeadTexture == nullptr || noteTexture == nullptr || backgroundTexture == nullptr) {
        quitSDL(window, renderer, snakeTexture, snakeHeadTexture, noteTexture, wallTexture,backgroundTexture);
        return 1;
    }
    //PlayGround playGround(20, 20);
   // Snake snake(&playGround,&audioManager);
    SDL_Event event;
    Direction direction = snake.getDirection();
    cout<<playGround.getWidth()<<" ";
    cout<<playGround.getHeight();
    while (playGround.isGameRun()) {
        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {
                playGround.setGameRun(false);
            } else {
                UserInput input = getUserInputFromEvent(event);
                snake.processUserInput(input);
            }

        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        renderGame(renderer, &snake, &playGround, snakeTexture, snakeHeadTexture,noteTexture,wallTexture,backgroundTexture);
        snake.nextStep();
        vector<Position> haha;
        haha=snake.getBody();
        std::cout << "Snake Head Position: (" << haha[0].getx()<< ", " << haha[0].gety() << ")\n";
std::cout << "Playground Bounds: (0, 0, "
          << playGround.getWidth() * CELL_SIZE.width << ", "
          << playGround.getHeight() * CELL_SIZE.height << ")\n";

        //if (checkSnakeEatCherry(&playGround, &snake)) {
         //   snake.eatCherry();

       // }
       if (checkSnakeEatNote(&playGround, &snake)) { //thay doi
            snake.eatNote();

        }
        SDL_RenderPresent(renderer);

        SDL_Delay(100);

}    audioManager.stopMusic();
    quitSDL(window, renderer, snakeTexture, snakeHeadTexture,noteTexture,wallTexture,backgroundTexture);
    return 0;
}
