#ifndef RENDERER_H
#define RENDERER_H
#include <SDL.h>
#include <SDL_ttf.h>
#include "Snake.h"
#include "PlayGround.h"

class RendererDiem {
private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Color textColor;

    // Texture và vị trí cho điểm số
    SDL_Texture* scoreTexture;
    SDL_Rect scoreRect;
    int lastScore;

    // Texture và vị trí cho thời gian đếm ngược
    SDL_Texture* timeTexture;
    SDL_Rect timeRect;
    Uint32 lastTime; // Lưu thời gian trước đó để kiểm tra thay đổi

    // Texture và vị trí cho số nốt vàng
    SDL_Texture* goldNotesTexture;
    SDL_Rect goldNotesRect;
    int lastGoldNotes; // Lưu số nốt vàng trước đó để kiểm tra thay đổi

public:
    RendererDiem(SDL_Renderer* renderer_);
    ~RendererDiem();
    void render(const Snake& snake, const PlayGround& playGround);
    void updateScoreTexture(int score);
    void updateTimeTexture(Uint32 remainingTime); // Hàm cập nhật texture thời gian
    void updateGoldNotesTexture(int eaten, int required); // Hàm cập nhật texture số nốt vàng
};
#endif
