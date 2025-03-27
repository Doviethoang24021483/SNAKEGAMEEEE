
#include "EffectManager.h" // Include header file của class
#include <cmath>   //Tính toán hình học
#include <cstdlib> // Cấp phát số ngẫu nhiên
#include <iostream>
// Hàm khởi tạo của class
EffectManager::EffectManager(SDL_Renderer* renderer) : renderer(renderer) {
    // Gán SDL_Renderer được truyền vào cho biến thành viên renderer
}

// Hàm hủy của class
EffectManager::~EffectManager() {
    // Không cần làm gì ở đây vì vector particles tự động giải phóng bộ nhớ khi bị hủy
}

// Hàm tạo một hạt mới
Particle createParticle(int x, int y, SDL_Color color) {
    Particle particle; // Tạo một đối tượng Particle mới

    // Gán vị trí cho hạt
    particle.x = x;
    particle.y = y;

    // Tạo vận tốc ngẫu nhiên cho hạt
   float angle = ((float)rand() / RAND_MAX) * 2 * M_PI; // Random angle in radians
    float speed = ((float)rand() / RAND_MAX) * 2.0f + 1.0f; // Random speed

    particle.vx = cos(angle) * speed;
    particle.vy = sin(angle) * speed;
    // Gán thời gian tồn tại cho hạt
    particle.lifetime = 100; // Adjust lifetime as needed

    // Gán màu sắc cho hạt
    particle.color = color;

    return particle; // Trả về hạt đã tạo
}

// Hàm tạo hiệu ứng ăn nốt nhạc
void EffectManager::createEatEffect(int x, int y) {
    int particleCount = 50; // Số lượng hạt trong hiệu ứng

    SDL_Color particleColor = {255, 255, 0, 255}; // Màu vàng

    // Tạo các hạt và thêm chúng vào vector particles
    for (int i = 0; i < particleCount; ++i) {
        particles.push_back(createParticle(x, y, particleColor)); // Tạo và thêm hạt vào vector
    }
}

// Hàm cập nhật trạng thái của tất cả các hiệu ứng
void EffectManager::updateEffects() {
    // Lặp qua tất cả các hạt trong vector particles
     for (size_t i = 0; i < particles.size(); ++i) {
           particles[i].x += particles[i].vx;
        particles[i].y += particles[i].vy;
        particles[i].lifetime--;
           if (particles[i].lifetime <= 0) {
                particles.erase(particles.begin()+i);

            }
    }
}

// Hàm vẽ một hạt lên màn hình
void drawParticle(SDL_Renderer* renderer, const Particle& particle) {
    // Kiểm tra xem hạt còn tồn tại hay không
    if (particle.lifetime > 0) {
        // Đặt màu vẽ là màu của hạt với độ trong suốt dựa trên thời gian tồn tại
        SDL_SetRenderDrawColor(renderer, particle.color.r, particle.color.g, particle.color.b, (Uint8)((particle.lifetime / 100.0f) * 255));

        // Vẽ một điểm tại vị trí của hạt
        SDL_RenderDrawPoint(renderer, (int)particle.x, (int)particle.y);
    }
}

// Hàm vẽ tất cả các hiệu ứng lên màn hình
void EffectManager::drawEffects() {
    // Lặp qua tất cả các hạt trong vector particles
    for (const auto& particle : particles) {
        // Vẽ hạt lên màn hình
        drawParticle(renderer, particle);
    }
}
