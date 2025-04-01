// Renderer.cpp
#include "Renderer.h"
#include <sstream>
#include <iostream>
#include "SDL_utils.h"
RendererDiem::RendererDiem(SDL_Renderer* renderer_)
    : renderer(renderer_),
      scoreTexture(nullptr),
      timeTexture(nullptr),
      goldNotesTexture(nullptr),
      lastScore(-1),
      lastTime(0),
      lastGoldNotes(-1) {
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    font = TTF_OpenFont("arial.ttf", 24);
    if (!font) {
        std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    textColor = {255, 255, 255, 255};
}

RendererDiem::~RendererDiem() {
    if (scoreTexture) SDL_DestroyTexture(scoreTexture);
    if (timeTexture) SDL_DestroyTexture(timeTexture);
    if (goldNotesTexture) SDL_DestroyTexture(goldNotesTexture);
    TTF_CloseFont(font);
    TTF_Quit();
}

void RendererDiem::updateScoreTexture(int score) {
    if (scoreTexture) {
        SDL_DestroyTexture(scoreTexture);
        scoreTexture = nullptr;
    }

    std::stringstream ss;
    ss << "Score: " << score;
    std::string scoreText = ss.str();

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
    if (!textSurface) {
        std::cerr << "Unable to render text surface! TTF_Error: " << TTF_GetError() << std::endl;
        return;
    }

    scoreTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!scoreTexture) {
        std::cerr << "Unable to create texture from text! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        return;
    }

    scoreRect = {3, 3, textSurface->w, textSurface->h}; // Đặt trong vùng UI
    SDL_FreeSurface(textSurface);
}

void RendererDiem::updateTimeTexture(Uint32 remainingTime) {
    if (timeTexture) {
        SDL_DestroyTexture(timeTexture);
        timeTexture = nullptr;
    }

    std::stringstream ss;
    ss << "Time: " << remainingTime << "s";
    std::string timeText = ss.str();

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, timeText.c_str(), textColor);
    if (!textSurface) {
        std::cerr << "Unable to render time text surface! TTF_Error: " << TTF_GetError() << std::endl;
        return;
    }

    timeTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!timeTexture) {
        std::cerr << "Unable to create texture from time text! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        return;
    }

    timeRect = {150, 3, textSurface->w, textSurface->h}; // Đặt trong vùng UI, cách Score một chút
    SDL_FreeSurface(textSurface);
}

void RendererDiem::updateGoldNotesTexture(int eaten, int required) {
    if (goldNotesTexture) {
        SDL_DestroyTexture(goldNotesTexture);
        goldNotesTexture = nullptr;
    }

    std::stringstream ss;
    ss << "Gold Notes: " << eaten << "/" << required;
    std::string goldNotesText = ss.str();

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, goldNotesText.c_str(), textColor);
    if (!textSurface) {
        std::cerr << "Unable to render gold notes text surface! TTF_Error: " << TTF_GetError() << std::endl;
        return;
    }

    goldNotesTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!goldNotesTexture) {
        std::cerr << "Unable to create texture from gold notes text! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        return;
    }

    goldNotesRect = {300, 3, textSurface->w, textSurface->h}; // Đặt trong vùng UI, cách Time một chút
    SDL_FreeSurface(textSurface);
}

void RendererDiem::render(const Snake& snake, const PlayGround& playGround) {
    // Vẽ nền cho vùng UI
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255); // Màu xám đậm
    SDL_Rect uiRect = {0, 0, SCREEN_WIDTH, UI_HEIGHT};
    SDL_RenderFillRect(renderer, &uiRect);

    // Vẽ đường viền phân cách giữa vùng UI và khu vực chơi game
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Màu trắng
    SDL_RenderDrawLine(renderer, 0, UI_HEIGHT, SCREEN_WIDTH, UI_HEIGHT);

    // Cập nhật và vẽ điểm số
    int currentScore = playGround.getScore();
    if (currentScore != lastScore) {
        updateScoreTexture(currentScore);
        lastScore = currentScore;
    }
    if (scoreTexture) {
        SDL_RenderCopy(renderer, scoreTexture, nullptr, &scoreRect);
    }

    // Nếu đang ở chế độ bản giao hưởng, hiển thị thời gian và số nốt vàng
    if (playGround.isInSymphonyMode()) {
        // Cập nhật thời gian đếm ngược
        Uint32 elapsedTime = SDL_GetTicks() - playGround.getSymphonyStartTime();
        Uint32 remainingTime = (playGround.getSymphonyTimeLimit() > elapsedTime)
            ? (playGround.getSymphonyTimeLimit() - elapsedTime) / 1000
            : 0;

        if (remainingTime != lastTime) {
            updateTimeTexture(remainingTime);
            lastTime = remainingTime;
        }
        if (timeTexture) {
            SDL_RenderCopy(renderer, timeTexture, nullptr, &timeRect);
        }

        // Cập nhật số nốt vàng
        int currentGoldNotes = playGround.getGoldNotesEaten();
        if (currentGoldNotes != lastGoldNotes) {
            updateGoldNotesTexture(currentGoldNotes, playGround.getGoldNotesRequired());
            lastGoldNotes = currentGoldNotes;
        }
        if (goldNotesTexture) {
            SDL_RenderCopy(renderer, goldNotesTexture, nullptr, &goldNotesRect);
        }
    } else {
        if (timeTexture) {
            SDL_DestroyTexture(timeTexture);
            timeTexture = nullptr;
        }
        if (goldNotesTexture) {
            SDL_DestroyTexture(goldNotesTexture);
            goldNotesTexture = nullptr;
        }
        lastTime = 0;
        lastGoldNotes = -1;
    }
}
