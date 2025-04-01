#include "EffectManager.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include "PlayGround.h"
#include "SDL_utils.h"
const CellSize CELL_SIZE = {30,30};
// Hàm khởi tạo của class
EffectManager::EffectManager(SDL_Renderer* renderer) : renderer(renderer) {
}

// Hàm hủy của class
EffectManager::~EffectManager() {
}

// Hàm tạo một hạt mới
Particle createParticle(int x, int y, SDL_Color color, int lifetime = 10) {
    Particle particle;

    particle.x = x;
    particle.y = y;

    float angle = ((float)rand() / RAND_MAX) * 2 * M_PI;
    float speed = ((float)rand() / RAND_MAX) * 2.0f + 1.0f;

    particle.vx = cos(angle) * speed;
    particle.vy = sin(angle) * speed;

    particle.lifetime = lifetime; // Thời gian tồn tại của hạt
    particle.color = color;

    return particle;
}

// Hàm tạo hiệu ứng ăn nốt nhạc thông thường
void EffectManager::createEatEffect(int x, int y) {
    int particleCount = 100;
    SDL_Color particleColor = {255, 255, 0, 255}; // Màu vàng cho nốt thông thường
    for (int i = 0; i < particleCount; ++i) {
        particles.push_back(createParticle(x, y, particleColor));
    }
}

// Hàm tạo hiệu ứng lấp lánh cho nốt vàng
void EffectManager::createSparkleEffect(int x, int y) {
    int particleCount = 150; // Tăng số lượng hạt để lấp lánh hơn
    SDL_Color particleColor = {255, 215, 0, 255}; // Màu vàng sáng cho nốt vàng
    for (int i = 0; i < particleCount; ++i) {
        // Dịch tọa độ y xuống dưới vùng UI và đặt hạt ở giữa ô
        Particle particle = createParticle(x + CELL_SIZE.width / 2, y + CELL_SIZE.height / 2 + GAME_AREA_OFFSET_Y, particleColor, 20); // Tăng thời gian tồn tại
        particles.push_back(particle);
    }
}

// Hàm cập nhật trạng thái của tất cả các hiệu ứng
void EffectManager::updateEffects() {
    for (size_t i = 0; i < particles.size();) {
        particles[i].x += particles[i].vx;
        particles[i].y += particles[i].vy;
        particles[i].lifetime--;

        if (particles[i].lifetime <= 0) {
            particles.erase(particles.begin() + i);
        } else {
            ++i;
        }
    }
}

// Hàm vẽ một hạt
void drawParticle(SDL_Renderer* renderer, const Particle& particle) {
    if (particle.lifetime > 0) {
        // Tính độ trong suốt dựa trên thời gian tồn tại
        Uint8 alpha = (Uint8)((particle.lifetime / 20.0f) * 255); // Điều chỉnh dựa trên lifetime tối đa
        SDL_SetRenderDrawColor(renderer, particle.color.r, particle.color.g, particle.color.b, alpha);

        // Vẽ hình tròn thay vì điểm
        int radius = 3;
        for (int w = -radius; w <= radius; w++) {
            for (int h = -radius; h <= radius; h++) {
                if (w * w + h * h <= radius * radius) {
                    SDL_RenderDrawPoint(renderer, (int)particle.x + w, (int)particle.y + h);
                }
            }
        }
    }
}

// Hàm vẽ tất cả các hiệu ứng lên màn hình
void EffectManager::drawEffects() {
    for (const auto& particle : particles) {
        drawParticle(renderer, particle);
    }
}
