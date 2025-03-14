#include <SDL.h>
#include <iostream>
#include "Position.h"
#include "PlayGround.h"
#include "SDL_utils.h"
#include "Snake.h"
#include <vector>

struct CellSize {
    int width;
    int height;
};

const CellSize CELL_SIZE = {26,27}; // Kích thước cho thân rắn
//const CellSize SNAKE_HEAD_SIZE = {31,28}; // Kích thước cho đầu rắn

//Ham ve nen mau tim va cac o vuong mau trang
void drawGrid(SDL_Renderer* renderer, int cellWidth, int cellHeight) {
    SDL_SetRenderDrawColor(renderer, 128, 0, 128, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int x = 0; x < SCREEN_WIDTH; x += cellWidth) {
        for (int y = 0; y < SCREEN_HEIGHT; y += cellHeight) {
            SDL_Rect cell = { x, y, cellWidth, cellHeight };
            SDL_RenderDrawRect(renderer, &cell);
        }
    }
    SDL_RenderPresent(renderer);
}

void drawSnakeSegment(SDL_Renderer* renderer, int x, int y, int width, int height, SDL_Texture* texture) {
    SDL_Rect destRect = { x, y, width, height };
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
}

void drawSnakeHead(SDL_Renderer* renderer, int x, int y, int width, int height, SDL_Texture* texture, double angle) {
    SDL_Rect destRect = { x, y, width, height };
    SDL_Point center = { width / 2, height / 2 }; // Rotation center
    SDL_RenderCopyEx(renderer, texture, NULL, &destRect, angle, &center, SDL_FLIP_NONE);
}

void drawCherry(SDL_Renderer* renderer, int x, int y, int width, int height,SDL_Texture* cherryTexture) {
    SDL_Rect desrect = { x, y, width, height };
    SDL_RenderCopy(renderer, cherryTexture,NULL, &desrect);
}

void renderGame(SDL_Renderer* renderer, Snake* snake, PlayGround* playGround, SDL_Texture* snakeTexture, SDL_Texture* snakeHeadTexture, SDL_Texture* cherryTexture) {
    drawGrid(renderer, CELL_SIZE.width, CELL_SIZE.height);
    Position cherryPos = playGround->getCherry();
    int cherryX = cherryPos.getx() * CELL_SIZE.width;
    int cherryY = cherryPos.gety() * CELL_SIZE.height;

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
        drawSnakeSegment(renderer, snakeX, snakeY, CELL_SIZE.width, CELL_SIZE.height, snakeTexture);
    }

    drawCherry(renderer, cherryX, cherryY, CELL_SIZE.width, CELL_SIZE.height,cherryTexture);
    SDL_RenderPresent(renderer);
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

bool checkSnakeEatCherry(PlayGround* playGround, Snake* snake) {
    Position snakeHead = snake->getBody().front();
    Position cherryPos = playGround->getCherry();
    if (snakeHead.getx() == cherryPos.getx() && snakeHead.gety() == cherryPos.gety()) {
        return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* snakeTexture = nullptr;
    SDL_Texture* snakeHeadTexture = nullptr;
    SDL_Texture* cherryTexture = nullptr;

    initSDL(window, renderer);

    // Đảm bảo rằng tên file ảnh là chính xác và các file ảnh nằm trong cùng thư mục với main.cpp
    snakeTexture = loadTexture("snake_body.png", renderer);
    cherryTexture = loadTexture("cherry.png", renderer);
    if (snakeTexture == nullptr) {
        quitSDL(window, renderer, snakeTexture, snakeHeadTexture,cherryTexture);
        return 1;
    }
    snakeHeadTexture = loadTexture("snake_head.png", renderer);
    if (snakeHeadTexture == nullptr) {
        quitSDL(window, renderer, snakeTexture, snakeHeadTexture,cherryTexture);
        return 1;
    }
     if (cherryTexture == nullptr) {
        quitSDL(window, renderer, snakeTexture, snakeHeadTexture, cherryTexture);
        return 1;
    }
    PlayGround playGround(20, 20);
    Snake snake(&playGround);
    SDL_Event event;
    Direction direction = snake.getDirection();
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
        renderGame(renderer, &snake, &playGround, snakeTexture, snakeHeadTexture,cherryTexture);
        snake.nextStep();
        if (checkSnakeEatCherry(&playGround, &snake)) {
            snake.eatCherry();

        }
        SDL_RenderPresent(renderer);

        SDL_Delay(170);
    }

    quitSDL(window, renderer, snakeTexture, snakeHeadTexture,cherryTexture);
    return 0;
}
