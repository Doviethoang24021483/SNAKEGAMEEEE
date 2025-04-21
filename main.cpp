#include <SDL.h>
#include <iostream>
#include "Position.h"
#include "PlayGround.h"
#include "SDL_utils.h"
#include "Snake.h"
#include <vector>
#include "AudioManager.h"
#include "EffectManager.h"
#include<cmath>
#include "Renderer.h"

const CellSize CELL_SIZE = {30,30}; //Kich thuoc o
    void showSplashScreen(SDL_Renderer* renderer, SDL_Texture* splashTexture) {
    bool waiting = true;
    SDL_Event event;

    while (waiting) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                exit(0);  // Thoát game nếu người dùng nhấn X
            }
            if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN) {
                waiting = false;  // Bắt đầu game nếu người chơi nhấn phím hoặc click chuột
            }
        }

        // Xóa màn hình
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Vẽ màn hình chào mừng
        SDL_Rect destRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderCopy(renderer, splashTexture, NULL, &destRect);

        // Hiển thị lên màn hình
        SDL_RenderPresent(renderer);
    }
}

void drawBackground(SDL_Renderer* renderer, int cellWidth, int cellHeight, SDL_Texture* backgroundTexture) {
    // Vẽ nền cho khu vực chơi game (dịch xuống dưới vùng UI)
    SDL_Rect destRect = {0, GAME_AREA_OFFSET_Y, SCREEN_WIDTH, SCREEN_HEIGHT - GAME_AREA_OFFSET_Y};
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &destRect);

    // Vẽ lưới
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 50); // Màu xám mờ
    for (int x = 0; x < SCREEN_WIDTH; x += cellWidth) {
        SDL_RenderDrawLine(renderer, x, GAME_AREA_OFFSET_Y, x, SCREEN_HEIGHT);
    }
    for (int y = GAME_AREA_OFFSET_Y; y < SCREEN_HEIGHT; y += cellHeight) {
        SDL_RenderDrawLine(renderer, 0, y, SCREEN_WIDTH, y);
    }
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

void drawNote(SDL_Renderer* renderer, int x, int y, int width, int height,SDL_Texture* noteTexture,PlayGround *playGround, SDL_Texture* noteTargetTexture,NoteValue currentValue,SDL_Texture* goldNoteTexture) {
    SDL_Rect desrect = { x, y, width, height };
    if(playGround->isInSymphonyMode() == true){

         SDL_RenderCopy(renderer,goldNoteTexture ,NULL,&desrect);
    }
    else{
    if (playGround->isNoteGuiding() && (SDL_GetTicks() - playGround->getGuideStartTime() < playGround->getGuideDuration())&& currentValue == playGround->noteSequence[playGround->currentNoteIndex]) {
        double angle = sin((SDL_GetTicks() - playGround->getGuideStartTime()) / 100.0) * 10.0; // Tạo góc lắc lư
        SDL_Point center = { width / 2, height / 2 };
    if( x== playGround->getTargetNote().position.getx()*CELL_SIZE.width && y == playGround->getTargetNote().position.gety()*CELL_SIZE.height){
        SDL_RenderCopyEx(renderer,noteTargetTexture, NULL,&desrect,angle,&center,SDL_FLIP_NONE );
    }
    else{

     SDL_RenderCopyEx(renderer, noteTexture, NULL, &desrect, angle, &center, SDL_FLIP_NONE);
    }
}
else{
    if( x== playGround->getTargetNote().position.getx()*CELL_SIZE.width && y == playGround->getTargetNote().position.gety()*CELL_SIZE.height){
            SDL_RenderCopy(renderer,noteTargetTexture,NULL,&desrect);}
    else{
        SDL_RenderCopy(renderer,noteTexture,NULL,&desrect);
    }
}
}
}
void renderGame(SDL_Renderer* renderer, Snake* snake, PlayGround* playGround, SDL_Texture* snakeTexture, SDL_Texture* snakeHeadTexture, SDL_Texture* noteTexture, SDL_Texture* backgroundTexture, SDL_Texture* noteTargetTexture,SDL_Texture* goldNoteTexture) {
    drawBackground(renderer, CELL_SIZE.width, CELL_SIZE.height,backgroundTexture);
     const vector<Note>& notes = playGround->getNotes();
    for (const Note& note : notes) {
        int noteX = note.position.getx() * CELL_SIZE.width;
        int noteY = note.position.gety() * CELL_SIZE.height;
        drawNote(renderer, noteX, noteY, CELL_SIZE.width, CELL_SIZE.height, noteTexture,playGround ,noteTargetTexture,note.value,goldNoteTexture);
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
}
UserInput getUserInputFromEvent(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym)// ma cua phim dc nhan
        {
        case SDLK_UP: return UserInput::KEY_UP;
        case SDLK_DOWN: return UserInput::KEY_DOWN;
        case SDLK_LEFT: return UserInput::KEY_LEFT;
        case SDLK_RIGHT: return UserInput::KEY_RIGHT;

        }
    }
    return UserInput::NO_INPUT;
}

 bool checkSnakeEatNote(PlayGround* playGround, Snake* snake) {
    Position snakeHead = snake->getBody().front();
    const vector<Note>& notes = playGround->getNotes();
    for (const Note& note : notes) {
        if (snakeHead.getx() == note.position.getx() && snakeHead.gety() == note.position.gety()) {
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
    SDL_Texture* noteTexture = nullptr;
    SDL_Texture* wallTexture = nullptr;
    SDL_Texture* backgroundTexture = nullptr;
    SDL_Texture* splashScreen = nullptr;
    SDL_Texture* noteTargetTexture = nullptr;
    SDL_Texture* goldNoteTexture = nullptr; // Texture cho nốt vàng
    initSDL(window, renderer);
    rendererkk = new RendererDiem(renderer); // Khởi tạo rendererkk
    AudioManager audioManager;
    EffectManager effectmanager(renderer);
    if (!audioManager.loadMusic("music.mp3")) {
        std::cerr << "Failed to load music!" << std::endl;
        quitSDL(window, renderer, snakeTexture, snakeHeadTexture, noteTexture, wallTexture, backgroundTexture, splashScreen,noteTargetTexture,goldNoteTexture);
        return -1;
    }
    if (!audioManager.loadFailChunk("fail.mp3")) {
        std::cerr << "Failed to load note chunks!" << std::endl;
        quitSDL(window, renderer, snakeTexture, snakeHeadTexture, noteTexture, wallTexture, backgroundTexture,splashScreen,noteTargetTexture,goldNoteTexture);
        return -1;
    }
     if (!audioManager.loadNoteChunk(NOTE_C, "C.mp3")) {
        std::cerr << "Failed to load C sound effect!" << std::endl;
        quitSDL(window, renderer, snakeTexture, snakeHeadTexture, noteTexture, wallTexture, backgroundTexture, splashScreen, noteTargetTexture,goldNoteTexture);
        return -1;
    }
        if (!audioManager.loadNoteChunk(NOTE_D, "D.mp3")) {
        std::cerr << "Failed to load D sound effect!" << std::endl;
        quitSDL(window, renderer, snakeTexture, snakeHeadTexture, noteTexture, wallTexture, backgroundTexture, splashScreen, noteTargetTexture,goldNoteTexture);
        return -1;
    }
        if (!audioManager.loadNoteChunk(NOTE_E, "E.mp3")) {
        std::cerr << "Failed to load E sound effect!" << std::endl;
        quitSDL(window, renderer, snakeTexture, snakeHeadTexture, noteTexture, wallTexture, backgroundTexture, splashScreen, noteTargetTexture,goldNoteTexture);
        return -1;
    }
    if (!audioManager.loadNoteChunk(NOTE_F, "F.mp3")) {
        std::cerr << "Failed to load F sound effect!" << std::endl;
        quitSDL(window, renderer, snakeTexture, snakeHeadTexture, noteTexture, wallTexture, backgroundTexture, splashScreen, noteTargetTexture,goldNoteTexture);
        return -1;
    }
        if (!audioManager.loadNoteChunk(NOTE_G, "G.mp3")) {
        std::cerr << "Failed to load G sound effect!" << std::endl;
        quitSDL(window, renderer, snakeTexture, snakeHeadTexture, noteTexture, wallTexture, backgroundTexture, splashScreen, noteTargetTexture,goldNoteTexture);
        return -1;
    }
     if (!audioManager.loadCompleteSong("complete.mp3")) {
        std::cerr << "Failed to load complete song!" << std::endl;
        quitSDL(window, renderer, snakeTexture, snakeHeadTexture, noteTexture, wallTexture, backgroundTexture, splashScreen, noteTargetTexture,goldNoteTexture);
        return -1;
    }
    if (!audioManager.loadGoldNoteSound("gold.mp3")) {
        std::cerr << "Failed to load gold note sound!" << std::endl;
        quitSDL(window, renderer, snakeTexture, snakeHeadTexture, noteTexture, wallTexture, backgroundTexture, splashScreen, noteTargetTexture, goldNoteTexture);
        return -1;
    }
     audioManager.setMusicVolume(30);
     audioManager.playMusic(); // Phát nhạc khi game bắt đầu
    PlayGround playGround(20, 20);
    Snake snake(&playGround, &audioManager, &effectmanager);

    snakeTexture = loadTexture("snake_body.png", renderer);
    noteTexture = loadTexture("note.png", renderer);
    noteTargetTexture = loadTexture("noteTarget.png", renderer);
    snakeHeadTexture = loadTexture("snake_head.png", renderer);
    backgroundTexture = loadTexture("background.png", renderer);
    splashScreen = loadTexture("splashscreen.png", renderer);
    goldNoteTexture = loadTexture("gold_note.png", renderer); // Tải texture cho nốt vàng
    if (snakeTexture == nullptr || snakeHeadTexture == nullptr || noteTexture == nullptr || backgroundTexture == nullptr || splashScreen == nullptr || noteTargetTexture == nullptr || goldNoteTexture== nullptr) {
        quitSDL(window, renderer, snakeTexture, snakeHeadTexture, noteTexture, wallTexture, backgroundTexture, splashScreen, noteTargetTexture, goldNoteTexture);
        return 1;
    }

    showSplashScreen(renderer, splashScreen);
    SDL_Event event;
    RendererDiem rendererkk(renderer); // Truyền renderer hợp lệ
bool quitGame = false;
    while (!quitGame) {
        SDL_Event event;
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
            snake.nextStep();
            if (checkSnakeEatNote(&playGround, &snake)) {
                snake.eatNote();
            }
            playGround.checkSymphonyStatus();
            if (!playGround.isGameRun()) {
           if(playGround.getStatus() == GAMEWON){
              bool playAgain = rendererkk.showMessage("YOU WIN", {0, 255, 0, 255});
            if (playAgain) {
                snake.reset();
                playGround.reset();
            } else {
                quitGame = true;
            }
        }
    }
            renderGame(renderer, &snake, &playGround, snakeTexture, snakeHeadTexture, noteTexture, backgroundTexture, noteTargetTexture, goldNoteTexture);
            rendererkk.render(snake, playGround);
            effectmanager.updateEffects();
            effectmanager.drawEffects();
            SDL_RenderPresent(renderer);
            SDL_Delay(200);
        }


    }
    waitUntilKeyPressed();
    audioManager.stopMusic();
    audioManager.~AudioManager();
    quitSDL(window, renderer, snakeTexture, snakeHeadTexture, noteTexture, wallTexture, backgroundTexture, splashScreen, noteTargetTexture,goldNoteTexture);
    return 0;
}
